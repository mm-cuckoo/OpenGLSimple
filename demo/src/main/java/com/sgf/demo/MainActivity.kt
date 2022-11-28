package com.sgf.demo

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import com.sgf.gl20.ui.main.GL20MainActivity
import com.sgf.gl30.ui.main.GL30MainActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<Button>(R.id.btn_gl20).setOnClickListener {
            val intentGl20 = Intent(this, GL20MainActivity::class.java)
            startActivity(intentGl20)
        }

        findViewById<Button>(R.id.btn_gl30).setOnClickListener {
            val intentGl30 = Intent(this, GL30MainActivity::class.java)
            startActivity(intentGl30)
        }
    }
}