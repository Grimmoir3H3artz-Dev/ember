#pragma once

/* Minimal OpenGL 4.6 Core loader used by Ember. */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*GLADuserptrloadfunc)(void* userptr, const char* name);

#ifndef APIENTRY
#if defined(_WIN32)
#define APIENTRY __stdcall
#else
#define APIENTRY
#endif
#endif

#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;

#define GL_FALSE 0
#define GL_TRUE 1
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_TRIANGLES 0x0004
#define GL_UNSIGNED_BYTE 0x1401
#define GL_UNSIGNED_INT 0x1405
#define GL_FLOAT 0x1406
#define GL_RGB 0x1907
#define GL_RGBA 0x1908
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_DEPTH_TEST 0x0B71
#define GL_CULL_FACE 0x0B44
#define GL_VERSION 0x1F02
#define GL_RENDERER 0x1F01
#define GL_VENDOR 0x1F00
#define GL_NO_ERROR 0
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_REPEAT 0x2901
#define GL_LINEAR 0x2601
#define GL_LINEAR_MIPMAP_LINEAR 0x2703
#define GL_TEXTURE0 0x84C0
#define GL_UNPACK_ALIGNMENT 0x0CF5

typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield);
typedef void (APIENTRYP PFNGLVIEWPORTPROC)(GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLENABLEPROC)(GLenum);
typedef const GLubyte* (APIENTRYP PFNGLGETSTRINGPROC)(GLenum);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC)(void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const void*);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void*);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC)(GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum);
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC)(GLenum, GLint);

extern PFNGLCLEARCOLORPROC glad_glClearColor;
extern PFNGLCLEARPROC glad_glClear;
extern PFNGLVIEWPORTPROC glad_glViewport;
extern PFNGLENABLEPROC glad_glEnable;
extern PFNGLGETSTRINGPROC glad_glGetString;
extern PFNGLGETERRORPROC glad_glGetError;
extern PFNGLCREATESHADERPROC glad_glCreateShader;
extern PFNGLSHADERSOURCEPROC glad_glShaderSource;
extern PFNGLCOMPILESHADERPROC glad_glCompileShader;
extern PFNGLGETSHADERIVPROC glad_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog;
extern PFNGLDELETESHADERPROC glad_glDeleteShader;
extern PFNGLCREATEPROGRAMPROC glad_glCreateProgram;
extern PFNGLATTACHSHADERPROC glad_glAttachShader;
extern PFNGLLINKPROGRAMPROC glad_glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glad_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog;
extern PFNGLUSEPROGRAMPROC glad_glUseProgram;
extern PFNGLDELETEPROGRAMPROC glad_glDeleteProgram;
extern PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation;
extern PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv;
extern PFNGLUNIFORM3FVPROC glad_glUniform3fv;
extern PFNGLUNIFORM1IPROC glad_glUniform1i;
extern PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays;
extern PFNGLGENBUFFERSPROC glad_glGenBuffers;
extern PFNGLBINDBUFFERPROC glad_glBindBuffer;
extern PFNGLBUFFERDATAPROC glad_glBufferData;
extern PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer;
extern PFNGLDRAWARRAYSPROC glad_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC glad_glDrawElements;
extern PFNGLGENTEXTURESPROC glad_glGenTextures;
extern PFNGLBINDTEXTUREPROC glad_glBindTexture;
extern PFNGLDELETETEXTURESPROC glad_glDeleteTextures;
extern PFNGLTEXIMAGE2DPROC glad_glTexImage2D;
extern PFNGLTEXPARAMETERIPROC glad_glTexParameteri;
extern PFNGLGENERATEMIPMAPPROC glad_glGenerateMipmap;
extern PFNGLACTIVETEXTUREPROC glad_glActiveTexture;
extern PFNGLPIXELSTOREIPROC glad_glPixelStorei;

#define glClearColor glad_glClearColor
#define glClear glad_glClear
#define glViewport glad_glViewport
#define glEnable glad_glEnable
#define glGetString glad_glGetString
#define glGetError glad_glGetError
#define glCreateShader glad_glCreateShader
#define glShaderSource glad_glShaderSource
#define glCompileShader glad_glCompileShader
#define glGetShaderiv glad_glGetShaderiv
#define glGetShaderInfoLog glad_glGetShaderInfoLog
#define glDeleteShader glad_glDeleteShader
#define glCreateProgram glad_glCreateProgram
#define glAttachShader glad_glAttachShader
#define glLinkProgram glad_glLinkProgram
#define glGetProgramiv glad_glGetProgramiv
#define glGetProgramInfoLog glad_glGetProgramInfoLog
#define glUseProgram glad_glUseProgram
#define glDeleteProgram glad_glDeleteProgram
#define glGetUniformLocation glad_glGetUniformLocation
#define glUniformMatrix4fv glad_glUniformMatrix4fv
#define glUniform3fv glad_glUniform3fv
#define glUniform1i glad_glUniform1i
#define glGenVertexArrays glad_glGenVertexArrays
#define glBindVertexArray glad_glBindVertexArray
#define glDeleteVertexArrays glad_glDeleteVertexArrays
#define glGenBuffers glad_glGenBuffers
#define glBindBuffer glad_glBindBuffer
#define glBufferData glad_glBufferData
#define glDeleteBuffers glad_glDeleteBuffers
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray
#define glVertexAttribPointer glad_glVertexAttribPointer
#define glDrawArrays glad_glDrawArrays
#define glDrawElements glad_glDrawElements
#define glGenTextures glad_glGenTextures
#define glBindTexture glad_glBindTexture
#define glDeleteTextures glad_glDeleteTextures
#define glTexImage2D glad_glTexImage2D
#define glTexParameteri glad_glTexParameteri
#define glGenerateMipmap glad_glGenerateMipmap
#define glActiveTexture glad_glActiveTexture
#define glPixelStorei glad_glPixelStorei

int gladLoadGLLoader(GLADuserptrloadfunc load, void* userptr);

#ifdef __cplusplus
}
#endif
