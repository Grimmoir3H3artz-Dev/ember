#include <glad/glad.h>

PFNGLCLEARCOLORPROC glad_glClearColor;
PFNGLCLEARPROC glad_glClear;
PFNGLVIEWPORTPROC glad_glViewport;
PFNGLENABLEPROC glad_glEnable;
PFNGLGETSTRINGPROC glad_glGetString;
PFNGLGETERRORPROC glad_glGetError;
PFNGLCREATESHADERPROC glad_glCreateShader;
PFNGLSHADERSOURCEPROC glad_glShaderSource;
PFNGLCOMPILESHADERPROC glad_glCompileShader;
PFNGLGETSHADERIVPROC glad_glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
PFNGLDELETESHADERPROC glad_glDeleteShader;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
PFNGLATTACHSHADERPROC glad_glAttachShader;
PFNGLLINKPROGRAMPROC glad_glLinkProgram;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
PFNGLUSEPROGRAMPROC glad_glUseProgram;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
PFNGLGENBUFFERSPROC glad_glGenBuffers;
PFNGLBINDBUFFERPROC glad_glBindBuffer;
PFNGLBUFFERDATAPROC glad_glBufferData;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
PFNGLDRAWARRAYSPROC glad_glDrawArrays;

int gladLoadGLLoader(GLADuserptrloadfunc load, void* userptr)
{
    if (!load) {
        return 0;
    }

    glad_glClearColor = (PFNGLCLEARCOLORPROC)load(userptr, "glClearColor");
    glad_glClear = (PFNGLCLEARPROC)load(userptr, "glClear");
    glad_glViewport = (PFNGLVIEWPORTPROC)load(userptr, "glViewport");
    glad_glEnable = (PFNGLENABLEPROC)load(userptr, "glEnable");
    glad_glGetString = (PFNGLGETSTRINGPROC)load(userptr, "glGetString");
    glad_glGetError = (PFNGLGETERRORPROC)load(userptr, "glGetError");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)load(userptr, "glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load(userptr, "glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load(userptr, "glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load(userptr, "glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load(userptr, "glGetShaderInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)load(userptr, "glDeleteShader");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load(userptr, "glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)load(userptr, "glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load(userptr, "glLinkProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load(userptr, "glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load(userptr, "glGetProgramInfoLog");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load(userptr, "glUseProgram");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)load(userptr, "glDeleteProgram");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)load(userptr, "glGetUniformLocation");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)load(userptr, "glUniformMatrix4fv");
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load(userptr, "glGenVertexArrays");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load(userptr, "glBindVertexArray");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)load(userptr, "glDeleteVertexArrays");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load(userptr, "glGenBuffers");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load(userptr, "glBindBuffer");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)load(userptr, "glBufferData");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)load(userptr, "glDeleteBuffers");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load(userptr, "glEnableVertexAttribArray");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load(userptr, "glVertexAttribPointer");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load(userptr, "glDrawArrays");

    return (glad_glCreateShader && glad_glDrawArrays) ? 1 : 0;
}
