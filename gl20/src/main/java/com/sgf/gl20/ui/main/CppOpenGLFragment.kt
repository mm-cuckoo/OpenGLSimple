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
class CppOpenGLFragment : Fragment() {

    private var _binding: FragmentMainBinding? = null

    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentMainBinding.inflate(inflater, container, false)
        val root = binding.root
        return root
    }

    companion object {
        @JvmStatic
        fun newInstance(): CppOpenGLFragment {
            return CppOpenGLFragment()
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}