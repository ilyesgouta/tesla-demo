
bin_PROGRAMS = tesla-demo

include_HEADERS = \
    load3ds/3ds.h \
    load3ds/Load3ds.h \
    3dlib/Motion.h \
    3dlib/Matrix.h \
    3dlib/Quater.h \
    3dlib/Map.h \
    3dlib/3dlib.h \
    3dlib/Vector.h \
    Demo/Smasher/ffd.h \
    Demo/Smasher/resource.h \
    Demo/Smasher/base.h

tesla_demo_CFLAGS = $(GL_CFLAGS) $(X11_CFLAGS)
tesla_demo_CXXFLAGS = $(GL_CFLAGS) $(X11_CFLAGS)

tesla_demo_LDFLAGS = $(GL_LIBS) $(X11_LIBS)

tesla_demo_SOURCES = \
    load3ds/Misc.c \
    load3ds/Mesh.c \
    load3ds/Material.c \
    load3ds/P_spline.c \
    load3ds/Load3ds.c \
    load3ds/Keyf.c \
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
    Demo/Smasher/Bands.cpp

#    Demo/Smasher/GridNode.cpp \
#    Demo/Smasher/Tree.cpp \
#    Demo/Smasher/LinePlane.cpp \
#    Demo/Smasher/ffd.cpp \
#    Demo/Smasher/SpinZoom.cpp \
#    Demo/Smasher/tubes.cpp \
#    Demo/Smasher/TerrainGen.cpp \
#    Demo/Smasher/Smasher.cpp \
#    Demo/Smasher/Dragon.cpp \
#    Demo/Smasher/Splines.cpp \
#    Demo/Smasher/FaceMorph.cpp \
#    Demo/Smasher/ShadeBall.cpp \
#    Demo/Smasher/Scape.cpp \
#    Demo/Smasher/tessellator.cpp \
#    Demo/Smasher/BassPlay.cpp \
#    Demo/Smasher/ScrewBolt.cpp \
#    Demo/Smasher/Rotator.cpp \
#    Demo/Smasher/EnergyStream.cpp \
#    Demo/Smasher/PolkaLike.cpp

CLEANFILES = $(BUILT_SOURCES)
