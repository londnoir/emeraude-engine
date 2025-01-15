/*
 * md2.c -- md2 model loader
 * last modification: aug. 14, 2007
 *
 * Copyright (c) 2005-2007 David HENRY
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * gcc -Wall -ansi -lGL -lGLU -lglut md2.c -o md2
 */

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Vector */
typedef float vec3_t[3];

/* MD2 header */
struct md2_header_t
{
  int ident;
  int version;

  int skinwidth;
  int skinheight;

  int framesize;

  int num_skins;
  int num_vertices;
  int num_st;
  int num_tris;
  int num_glcmds;
  int num_frames;

  int offset_skins;
  int offset_st;
  int offset_tris;
  int offset_frames;
  int offset_glcmds;
  int offset_end;
};

/* Texture name */
struct md2_skin_t
{
  char name[64];
};

/* Texture coords */
struct md2_texCoord_t
{
  short s;
  short t;
};

/* Triangle info */
struct md2_triangle_t
{
  unsigned short vertex[3];
  unsigned short st[3];
};

/* Compressed vertex */
struct md2_vertex_t
{
  unsigned char v[3];
  unsigned char normalIndex;
};

/* Model frame */
struct md2_frame_t
{
  vec3_t scale;
  vec3_t translate;
  char name[16];
  struct md2_vertex_t *verts;
};

/* GL command packet */
struct md2_glcmd_t
{
  float s;
  float t;
  int index;
};

/* MD2 model structure */
struct md2_model_t
{
  struct md2_header_t header;

  struct md2_skin_t *skins;
  struct md2_texCoord_t *texcoords;
  struct md2_triangle_t *triangles;
  struct md2_frame_t *frames;
  int *glcmds;

  GLuint tex_id;
};

/* Table of precalculated normals */
vec3_t anorms_table[162] = {
#include "anorms.h"
};

/*** An MD2 model ***/
struct md2_model_t md2file;


/**
 * Load an MD2 model from file.
 *
 * Note: MD2 format stores model's data in little-endian ordering.  On
 * big-endian machines, you'll have to perform proper conversions.
 */
int
ReadMD2Model (const char *filename, struct md2_model_t *mdl)
{
  FILE *fp;
  int i;

  fp = fopen (filename, "rb");
  if (!fp)
    {
      fprintf (stderr, "Error: couldn't open \"%s\"!\n", filename);
      return 0;
    }

  /* Read header */
  fread (&mdl->header, 1, sizeof (struct md2_header_t), fp);

  if ((mdl->header.ident != 844121161) ||
      (mdl->header.version != 8))
    {
      /* Error! */
      fprintf (stderr, "Error: bad version or identifier\n");
      fclose (fp);
      return 0;
    }

  /* Memory allocations */
  mdl->skins = (struct md2_skin_t *)
    malloc (sizeof (struct md2_skin_t) * mdl->header.num_skins);
  mdl->texcoords = (struct md2_texCoord_t *)
    malloc (sizeof (struct md2_texCoord_t) * mdl->header.num_st);
  mdl->triangles = (struct md2_triangle_t *)
    malloc (sizeof (struct md2_triangle_t) * mdl->header.num_tris);
  mdl->frames = (struct md2_frame_t *)
    malloc (sizeof (struct md2_frame_t) * mdl->header.num_frames);
  mdl->glcmds = (int *)malloc (sizeof (int) * mdl->header.num_glcmds);

  /* Read model data */
  fseek (fp, mdl->header.offset_skins, SEEK_SET);
  fread (mdl->skins, sizeof (struct md2_skin_t),
	 mdl->header.num_skins, fp);

  fseek (fp, mdl->header.offset_st, SEEK_SET);
  fread (mdl->texcoords, sizeof (struct md2_texCoord_t),
	 mdl->header.num_st, fp);

  fseek (fp, mdl->header.offset_tris, SEEK_SET);
  fread (mdl->triangles, sizeof (struct md2_triangle_t),
	 mdl->header.num_tris, fp);

  fseek (fp, mdl->header.offset_glcmds, SEEK_SET);
  fread (mdl->glcmds, sizeof (int), mdl->header.num_glcmds, fp);

  /* Read frames */
  fseek (fp, mdl->header.offset_frames, SEEK_SET);
  for (i = 0; i < mdl->header.num_frames; ++i)
    {
      /* Memory allocation for vertices of this frame */
      mdl->frames[i].verts = (struct md2_vertex_t *)
	malloc (sizeof (struct md2_vertex_t) * mdl->header.num_vertices);

      /* Read frame data */
      fread (mdl->frames[i].scale, sizeof (vec3_t), 1, fp);
      fread (mdl->frames[i].translate, sizeof (vec3_t), 1, fp);
      fread (mdl->frames[i].name, sizeof (char), 16, fp);
      fread (mdl->frames[i].verts, sizeof (struct md2_vertex_t),
	     mdl->header.num_vertices, fp);
    }

  fclose (fp);
  return 1;
}

/**
 * Free resources allocated for the model.
 */
void
FreeModel (struct md2_model_t *mdl)
{
  int i;

  if (mdl->skins)
    {
      free (mdl->skins);
      mdl->skins = NULL;
    }

  if (mdl->texcoords)
    {
      free (mdl->texcoords);
      mdl->texcoords = NULL;
    }

  if (mdl->triangles)
    {
      free (mdl->triangles);
      mdl->triangles = NULL;
    }

  if (mdl->glcmds)
    {
      free (mdl->glcmds);
      mdl->glcmds = NULL;
    }

  if (mdl->frames)
    {
      for (i = 0; i < mdl->header.num_frames; ++i)
	{
	  free (mdl->frames[i].verts);
	  mdl->frames[i].verts = NULL;
	}

      free (mdl->frames);
      mdl->frames = NULL;
    }
}

/**
 * Render the model at frame n.
 */
void
RenderFrame (int n, const struct md2_model_t *mdl)
{
  int i, j;
  GLfloat s, t;
  vec3_t v;
  struct md2_frame_t *pframe;
  struct md2_vertex_t *pvert;

  /* Check if n is in a valid range */
  if ((n < 0) || (n > mdl->header.num_frames - 1))
    return;

  /* Enable model's texture */
  glBindTexture (GL_TEXTURE_2D, mdl->tex_id);

  /* Draw the model */
  glBegin (GL_TRIANGLES);
    /* Draw each triangle */
    for (i = 0; i < mdl->header.num_tris; ++i)
      {
	/* Draw each vertex */
	for (j = 0; j < 3; ++j)
	  {
	    pframe = &mdl->frames[n];
	    pvert = &pframe->verts[mdl->triangles[i].vertex[j]];

	    /* Compute texture coordinates */
	    s = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].s / mdl->header.skinwidth;
	    t = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].t / mdl->header.skinheight;

	    /* Pass texture coordinates to OpenGL */
	    glTexCoord2f (s, t);

	    /* Normal vector */
	    glNormal3fv (anorms_table[pvert->normalIndex]);

	    /* Calculate vertex real position */
	    v[0] = (pframe->scale[0] * pvert->v[0]) + pframe->translate[0];
	    v[1] = (pframe->scale[1] * pvert->v[1]) + pframe->translate[1];
	    v[2] = (pframe->scale[2] * pvert->v[2]) + pframe->translate[2];

	    glVertex3fv (v);
	  }
      }
  glEnd ();
}

/**
 * Render the model with interpolation between frame n and n+1.
 * interp is the interpolation percent. (from 0.0 to 1.0)
 */
void
RenderFrameItp (int n, float interp, const struct md2_model_t *mdl)
{
  int i, j;
  GLfloat s, t;
  vec3_t v_curr, v_next, v, norm;
  float *n_curr, *n_next;
  struct md2_frame_t *pframe1, *pframe2;
  struct md2_vertex_t *pvert1, *pvert2;

  /* Check if n is in a valid range */
  if ((n < 0) || (n > mdl->header.num_frames))
    return;

  /* Enable model's texture */
  glBindTexture (GL_TEXTURE_2D, mdl->tex_id);

  /* Draw the model */
  glBegin (GL_TRIANGLES);
    /* Draw each triangle */
    for (i = 0; i < mdl->header.num_tris; ++i)
      {
	/* Draw each vertex */
	for (j = 0; j < 3; ++j)
	  {
	    pframe1 = &mdl->frames[n];
	    pframe2 = &mdl->frames[n + 1];
	    pvert1 = &pframe1->verts[mdl->triangles[i].vertex[j]];
	    pvert2 = &pframe2->verts[mdl->triangles[i].vertex[j]];

	    /* Compute texture coordinates */
	    s = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].s / mdl->header.skinwidth;
	    t = (GLfloat)mdl->texcoords[mdl->triangles[i].st[j]].t / mdl->header.skinheight;

	    /* Pass texture coordinates to OpenGL */
	    glTexCoord2f (s, t);

	    /* Interpolate normals */
	    n_curr = anorms_table[pvert1->normalIndex];
	    n_next = anorms_table[pvert2->normalIndex];

	    norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
	    norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
	    norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

	    glNormal3fv (norm);

	    /* Interpolate vertices */
	    v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
	    v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
	    v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

	    v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
	    v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
	    v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

	    v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
	    v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
	    v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);

	    glVertex3fv (v);
	  }
      }
  glEnd ();
}

/**
 * Render the model at frame n using model's GL command list.
 */
void
RenderFrameWithGLCmds (int n, const struct md2_model_t *mdl)
{
  int i, *pglcmds;
  vec3_t v;
  struct md2_frame_t *pframe;
  struct md2_vertex_t *pvert;
  struct md2_glcmd_t *packet;

  /* Check if n is in a valid range */
  if ((n < 0) || (n > mdl->header.num_frames - 1))
    return;

  /* Enable model's texture */
  glBindTexture (GL_TEXTURE_2D, mdl->tex_id);

  /* pglcmds points at the start of the command list */
  pglcmds = mdl->glcmds;

  /* Draw the model */
  while ((i = *(pglcmds++)) != 0)
    {
      if (i < 0)
	{
	  glBegin (GL_TRIANGLE_FAN);
	  i = -i;
	}
      else
	{
	  glBegin (GL_TRIANGLE_STRIP);
	}

      /* Draw each vertex of this group */
      for (/* Nothing */; i > 0; --i, pglcmds += 3)
	{
	  packet = (struct md2_glcmd_t *)pglcmds;
	  pframe = &mdl->frames[n];
	  pvert = &pframe->verts[packet->index];

	  /* Pass texture coordinates to OpenGL */
	  glTexCoord2f (packet->s, packet->t);

	  /* Normal vector */
	  glNormal3fv (anorms_table[pvert->normalIndex]);

	  /* Calculate vertex real position */
	  v[0] = (pframe->scale[0] * pvert->v[0]) + pframe->translate[0];
	  v[1] = (pframe->scale[1] * pvert->v[1]) + pframe->translate[1];
	  v[2] = (pframe->scale[2] * pvert->v[2]) + pframe->translate[2];

	  glVertex3fv (v);
	}

      glEnd ();
    }
}

/**
 * Render the model with interpolation between frame n and n+1
 * using model's GL command list.
 * interp is the interpolation percent. (from 0.0 to 1.0)
 */
void
RenderFrameItpWithGLCmds (int n, float interp, const struct md2_model_t *mdl)
{
  int i, *pglcmds;
  vec3_t v_curr, v_next, v, norm;
  float *n_curr, *n_next;
  struct md2_frame_t *pframe1, *pframe2;
  struct md2_vertex_t *pvert1, *pvert2;
  struct md2_glcmd_t *packet;

  /* Check if n is in a valid range */
  if ((n < 0) || (n > mdl->header.num_frames - 1))
    return;

  /* Enable model's texture */
  glBindTexture (GL_TEXTURE_2D, mdl->tex_id);

  /* pglcmds points at the start of the command list */
  pglcmds = mdl->glcmds;

  /* Draw the model */
  while ((i = *(pglcmds++)) != 0)
    {
      if (i < 0)
	{
	  glBegin (GL_TRIANGLE_FAN);
	  i = -i;
	}
      else
	{
	  glBegin (GL_TRIANGLE_STRIP);
	}

      /* Draw each vertex of this group */
      for (/* Nothing */; i > 0; --i, pglcmds += 3)
	{
	  packet = (struct md2_glcmd_t *)pglcmds;
	  pframe1 = &mdl->frames[n];
	  pframe2 = &mdl->frames[n + 1];
	  pvert1 = &pframe1->verts[packet->index];
	  pvert2 = &pframe2->verts[packet->index];

	  /* Pass texture coordinates to OpenGL */
	  glTexCoord2f (packet->s, packet->t);

	  /* Interpolate normals */
	  n_curr = anorms_table[pvert1->normalIndex];
	  n_next = anorms_table[pvert2->normalIndex];

	  norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
	  norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
	  norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

	  glNormal3fv (norm);

	  /* Interpolate vertices */
	  v_curr[0] = pframe1->scale[0] * pvert1->v[0] + pframe1->translate[0];
	  v_curr[1] = pframe1->scale[1] * pvert1->v[1] + pframe1->translate[1];
	  v_curr[2] = pframe1->scale[2] * pvert1->v[2] + pframe1->translate[2];

	  v_next[0] = pframe2->scale[0] * pvert2->v[0] + pframe2->translate[0];
	  v_next[1] = pframe2->scale[1] * pvert2->v[1] + pframe2->translate[1];
	  v_next[2] = pframe2->scale[2] * pvert2->v[2] + pframe2->translate[2];

	  v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
	  v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
	  v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);

	  glVertex3fv (v);
	}

      glEnd ();
    }
}

/**
 * Calculate the current frame in animation beginning at frame
 * 'start' and ending at frame 'end', given interpolation percent.
 * interp will be reseted to 0.0 if the next frame is reached.
 */
void
Animate (int start, int end, int *frame, float *interp)
{
  if ((*frame < start) || (*frame > end))
    *frame = start;

  if (*interp >= 1.0f)
    {
      /* Move to next frame */
      *interp = 0.0f;
      (*frame)++;

      if (*frame >= end)
	*frame = start;
    }
}

void
init (const char *filename)
{
  GLfloat lightpos[] = { 5.0f, 10.0f, 0.0f, 1.0f };

  /* Initialize OpenGL context */
  glClearColor (0.5f, 0.5f, 0.5f, 1.0f);
  glShadeModel (GL_SMOOTH);

  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);

  glLightfv (GL_LIGHT0, GL_POSITION, lightpos);

  /* Load MD2 model file */
  if (!ReadMD2Model (filename, &md2file))
    exit (EXIT_FAILURE);
}

void
cleanup ()
{
  FreeModel (&md2file);
}

void
reshape (int w, int h)
{
  if (h == 0)
    h = 1;

  glViewport (0, 0, (GLsizei)w, (GLsizei)h);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45.0, w/(GLdouble)h, 0.1, 1000.0);

  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

void
display ()
{
  static int n = 0; /* The current frame */
  static float interp = 0.0;
  static double curent_time = 0;
  static double last_time = 0;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity ();

  last_time = curent_time;
  curent_time = (double)glutGet (GLUT_ELAPSED_TIME) / 1000.0;

  /* Animate model from frames 0 to num_frames-1 */
  interp += 10 * (curent_time - last_time);
  Animate (0, md2file.header.num_frames - 1, &n, &interp);

  glTranslatef (0.0f, 0.0f, -100.0f);
  glRotatef (-90.0f, 1.0, 0.0, 0.0);
  glRotatef (-90.0f, 0.0, 0.0, 1.0);

  /* Draw the model */
/* RenderFrame (n, md2file); */
/* RenderFrameWithGLCmds (n, md2file); */
/* RenderFrameItp (n, interp, md2file); */
  RenderFrameItpWithGLCmds (n, interp, &md2file);

  glutSwapBuffers ();
  glutPostRedisplay ();
}

void
keyboard (unsigned char key, int x, int y)
{
  /* Escape */
  if (key == 27)
    exit (0);
}

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <filename.md2>\n", argv[0]);
      return -1;
    }

  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize (640, 480);
  glutCreateWindow ("MD2 Model");

  atexit (cleanup);
  init (argv[1]);

  glutReshapeFunc (reshape);
  glutDisplayFunc (display);
  glutKeyboardFunc (keyboard);

  glutMainLoop ();

  return 0;
}
