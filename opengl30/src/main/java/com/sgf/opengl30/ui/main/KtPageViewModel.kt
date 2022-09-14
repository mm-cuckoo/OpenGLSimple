package com.sgf.opengl30.ui.main

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel

class KtPageViewModel : ViewModel() {

    val text: LiveData<String> = MutableLiveData("Kt Open GL Simple page :")

}