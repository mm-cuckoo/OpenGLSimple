package com.sgf.gl20.ui.main

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.sgf.gl20.databinding.FragmentMainBinding

/**
 * A placeholder fragment containing a simple view.
 */
class KtOpenGLFragment : Fragment() {

    private var viewBinding: FragmentMainBinding? = null
    private val binding get() = viewBinding!!
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        viewBinding = FragmentMainBinding.inflate(inflater, container, false)
        return binding.root
    }

    companion object {
        @JvmStatic
        fun newInstance(): KtOpenGLFragment {
            return KtOpenGLFragment()
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        viewBinding = null
    }
}