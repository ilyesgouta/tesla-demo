
bin_PROGRAMS = tesla-demo

include_HEADERS = \
    3dlib/Motion.h \
    3dlib/Matrix.h \
    3dlib/Quater.h \
    3dlib/Map.h \
    3dlib/3dlib.h \
    3dlib/Vector.h \
    Demo/Smasher/ffd.h \
    Demo/Smasher/resource.h \
    Demo/Smasher/base.h

AM_CFLAGS =
AM_CXXFLAGS =

tesla_demo_CFLAGS = -g3 -O2 -std=c++0x $(EGL_CFLAGS) $(GLESV1_CM_CFLAGS) $(directfb_CFLAGS) $(lib3ds_CFLAGS) $(libpng_CFLAGS) $(libmpg123_CFLAGS) $(alsa_CFLAGS)
tesla_demo_CXXFLAGS = -g3 -O2 -std=c++0x $(EGL_CFLAGS) $(GLESV1_CM_CFLAGS) $(directfb_CFLAGS) $(lib3ds_CFLAGS) $(libpng_CFLAGS) $(libmpg123_CFLAGS) $(alsa_CFLAGS)

tesla_demo_LDADD = $(EGL_LIBS) $(GLESV1_CM_LIBS) $(directfb_LIBS) $(libpng_LIBS) $(jpeg_LIBS) $(lib3ds_LIBS) $(libmpg123_LIBS) $(alsa_LIBS) -lrt -lpthread

tesla_demo_SOURCES = \
    3dlib/Quater.c \
    3dlib/Vector.c \
    3dlib/Matrix.c \
    OpenGL/OpenGL.cpp \
    OpenGL/Dyngl.cpp \
    base3d/Camera.cpp \
    base3d/CMatrix.cpp \
    base3d/Quaternion.cpp \
    ImageLib/ImageLib/Tga/LoadTGA.cpp \
    ImageLib/ImageLib/PNG/LoadPNG.cpp \
    ImageLib/ImageLib/JPEG/Loadjpg.cpp \
    ImageLib/ImageLib.cpp \
    MainFrame/MainFrame.cpp \
    Demo/Smasher/EffManage.cpp \
    Demo/Smasher/FFDEnvVector.cpp \
    Demo/Smasher/TexManager.cpp \
    Demo/Smasher/Stuff.cpp \
    Demo/Smasher/SpinZoom.cpp \
    Demo/Smasher/ShadeBall.cpp \
    Demo/Smasher/Splines.cpp \
    Demo/Smasher/Bands.cpp \
    Demo/Smasher/EnergyStream.cpp \
    Demo/Smasher/tubes.cpp \
    Demo/Smasher/tessellator.cpp \
    Demo/Smasher/PolkaLike.cpp \
    Demo/Smasher/Tree.cpp \
    Demo/Smasher/ffd.cpp \
    Demo/Smasher/FaceMorph.cpp \
    Demo/Smasher/LinePlane.cpp \
    Demo/Smasher/Scape.cpp \
    Demo/Smasher/GridNode.cpp \
    Demo/Smasher/TerrainGen.cpp \
    Demo/Smasher/Rotator.cpp \
    Demo/Smasher/Mpg123Audio.cpp \
    Demo/Smasher/Smasher.cpp

#    Demo/Smasher/Dragon.cpp \
#    Demo/Smasher/ScrewBolt.cpp \
#    Demo/Smasher/BassPlay.cpp

CLEANFILES = $(BUILT_SOURCES)
