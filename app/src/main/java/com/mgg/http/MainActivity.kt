package com.mgg.http

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.mgg.http.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.sampleText.setOnClickListener {
            binding.sampleText.text = stringFromJNI()
        }
        binding.sampleText.text = stringFromJNI()
    }

    /**
     * A native method that is implemented by the 'http' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'http' library on application startup.
        init {
            System.loadLibrary("http")
        }
    }
}