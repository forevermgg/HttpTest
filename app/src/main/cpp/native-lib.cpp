#include <curl/curl.h>
#include <jni.h>
#include <openssl/crypto.h>

#include <memory>
#include <string>

#include "client.h"
#include "curl_client.h"
#include "thread/ScopedThread.hpp"
#include "thread/SingleThreadExecutor.hpp"

size_t WriteCallback(void* contents, size_t size, size_t nmemb,
                     std::string* response) {
  size_t totalSize = size * nmemb;
  response->append((char*)contents, totalSize);
  return totalSize;
}

std::string testCurlOne() {
  CURL* curl;
  CURLcode res;
  std::string hello = "";
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if (curl) {
    const char* url = "https://dog.ceo/api/breeds/image/random";
    // https://images.dog.ceo/breeds/pekinese/n02086079_14208.jpg
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      hello =
          "curl_easy_perform failed: " + std::string(curl_easy_strerror(res));
    } else {
      hello = "curl_easy_perform ok: " + std::string(response);
    }
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return hello;
}

std::string testCurlTwo() {
  std::unique_ptr<ecclesia::CurlHttpClient> curl_http_client =
      std::make_unique<ecclesia::CurlHttpClient>(
          ecclesia::LibCurlProxy::CreateInstance());
  auto req = std::make_unique<ecclesia::HttpClient::HttpRequest>();
  req->uri = "https://dog.ceo/api/breeds/image/random";
  auto result = curl_http_client->Get(std::move(req));
  return result.value().body.c_str();
}

std::string testSingleThreadExecutor() {
  constexpr int kDefaultThreadCount = 10;
    struct Context {
        std::string result = "";
    };
    auto executor = std::make_unique<kotlin::SingleThreadExecutor<Context>>();
    auto future = executor->execute([&]{
        executor->context().result = "test";
    });
    future.get();
    auto result = executor->context().result;
    return result;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_mgg_http_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
  testSingleThreadExecutor();
  return env->NewStringUTF(testCurlTwo().c_str());
}