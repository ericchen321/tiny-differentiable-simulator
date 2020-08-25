// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <stdio.h>

#include "tiny_float_utils.h"
#include "tiny_vector3.h"
#include "examples/opengl_window/tiny_opengl3_app.h"
#include "examples/opengl_window/tiny_camera.h"



namespace py = pybind11;

PYBIND11_MODULE(pytinyopengl3, m) {
  m.doc() = R"pbdoc(
        tiny opengl3 graphics engine python binding
        -----------------------

        .. currentmodule:: pytinyopengl3

        .. autosummary::
           :toctree: _generate

    )pbdoc";

  py::class_<TinyOpenGL3App>(m,"TinyOpenGL3App")
    .def(py::init<const char*,int,int, bool, int, int, int, int>(),
      py::arg("title")="pytinyopengl3",
      py::arg("width")=1024,
      py::arg("height")=768,
      py::arg("allowRetina")=1,
      py::arg("windowType")=0,
      py::arg("renderDevice")=-1,
      py::arg("maxNumObjectCapacity")=128 * 1024,
      py::arg("maxShapeCapacityInBytes")=128 * 1024 * 1024)
      .def("swap_buffer", &TinyOpenGL3App::swap_buffer)
      .def("register_cube_shape", &TinyOpenGL3App::register_cube_shape)
      .def("register_graphics_unit_sphere_shape", &TinyOpenGL3App::register_graphics_unit_sphere_shape)
      .def("draw_grid", (void (TinyOpenGL3App::*)())&TinyOpenGL3App::draw_grid)
      .def("draw_text_3d", (void (TinyOpenGL3App::*)(const char*, float [3], float[4], float[4], float, int)) &TinyOpenGL3App::draw_text_3d)
      .def("draw_text_3d", (void (TinyOpenGL3App::*)(const char*, float, float, float, float)) &TinyOpenGL3App::draw_text_3d)
      .def_readwrite("renderer",&TinyOpenGL3App::m_renderer)
      ;
      
  
  py::class_<TinyCamera>(m, "TinyCamera")
    .def(py::init<>())
    .def("update", &TinyCamera::update)
    .def("set_camera_distance", &TinyCamera::set_camera_distance)
    .def("set_camera_pitch", &TinyCamera::set_camera_pitch)
    .def("set_camera_yaw", &TinyCamera::set_camera_yaw)
    .def("set_camera_up_vector",&TinyCamera::set_camera_up_vector)
    .def("set_camera_target_position", &TinyCamera::set_camera_target_position)
      ;
      
  py::class_<TinyGLInstancingRenderer>(m, "TinyGLInstancingRenderer")
    .def("init", &TinyGLInstancingRenderer::init)
    .def("register_graphics_instance", &TinyGLInstancingRenderer::register_graphics_instance)
    .def("update_camera", &TinyGLInstancingRenderer::update_camera)
    .def("render_scene", &TinyGLInstancingRenderer::render_scene)
      
    ;
      
  py::class_<TinyVector3<float, FloatUtils>>(m, "TinyVector3f")
      .def(py::init<float, float, float>())
      .def("set_zero", &TinyVector3<float, FloatUtils>::set_zero)
      .def_readwrite("x", &TinyVector3<float, FloatUtils>::m_x)
      .def_readwrite("y", &TinyVector3<float, FloatUtils>::m_y)
      .def_readwrite("z", &TinyVector3<float, FloatUtils>::m_z)
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self += py::self)
      .def(py::self -= py::self)
      .def(-py::self)
      .def("__repr__",
           [](const TinyVector3<float, FloatUtils> &a) {
             return "[" + std::to_string(a.m_x) + " " + std::to_string(a.m_y) +
                    " " + std::to_string(a.m_z) + "]";
           })
      .def("__getitem__", [](const TinyVector3<float, FloatUtils> &a,
                             int i) { return a[i]; })
      .def("__setitem__", [](TinyVector3<float, FloatUtils> &a, int i,
                             double v) { a[i] = v; });

  py::class_<TinyQuaternion<float, FloatUtils>>(m, "TinyQuaternionf")
      .def(py::init<float, float, float, float>())
      .def("set_identity", &TinyQuaternion<float, FloatUtils>::set_identity)
      .def("get_euler_rpy", &TinyQuaternion<float, FloatUtils>::get_euler_rpy)
      .def("get_euler_rpy2",
           &TinyQuaternion<float, FloatUtils>::get_euler_rpy2)
      .def("set_euler_rpy", &TinyQuaternion<float, FloatUtils>::set_euler_rpy)

      .def_readwrite("x", &TinyQuaternion<float, FloatUtils>::m_x)
      .def_readwrite("y", &TinyQuaternion<float, FloatUtils>::m_y)
      .def_readwrite("z", &TinyQuaternion<float, FloatUtils>::m_z)
      .def_readwrite("w", &TinyQuaternion<float, FloatUtils>::m_w)
      .def("__repr__",
           [](const TinyQuaternion<float, FloatUtils> &q) {
             return "[" + std::to_string(q.m_x) + " " + std::to_string(q.m_y) +
                    " " + std::to_string(q.m_z) + " " + std::to_string(q.m_w) +
                    "]";
           })
      .def("__getitem__", [](const TinyQuaternion<float, FloatUtils> &a,
                             int i) { return a[i]; })
      .def("__setitem__", [](TinyQuaternion<float, FloatUtils> &a, int i,
                             float v) { a[i] = v; });


#ifdef VERSION_INFO
  m.attr("__version__") = VERSION_INFO;
#else
  m.attr("__version__") = "dev";
#endif
 
}
