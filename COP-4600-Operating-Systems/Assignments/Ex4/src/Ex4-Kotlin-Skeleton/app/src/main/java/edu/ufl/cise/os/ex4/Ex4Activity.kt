package edu.ufl.cise.os.ex4

import android.app.Activity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText

class Ex4Activity : Activity() {

    private var leftButton: Button? = null
    private var rightButton: Button? = null
    private var leftText: EditText? = null
    private var rightText: EditText? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_ex4)

        rightButton = findViewById<Button>(R.id.rightButton)
        leftButton = findViewById<Button>(R.id.leftButton)
        rightText = findViewById<EditText>(R.id.rightText)
        leftText = findViewById<EditText>(R.id.leftText)
    }

    fun onLeftClick(view: View?) {
        // When the left button is clicked...

    }

    fun onRightClick(view: View?) {
        // When the right button is clicked...

    }
}
