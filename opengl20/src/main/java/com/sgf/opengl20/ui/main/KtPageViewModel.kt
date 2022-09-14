package com.sgf.opengl20.ui.main

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Transformations
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider

class KtPageViewModel : ViewModel() {

    val text: LiveData<String> = MutableLiveData("Kt Open GL Simple page :")

}