#ifndef __GRAPHIC_SURFACE_H__
#define __GRAPHIC_SURFACE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <stdint.h>
#include <graphic/point.h>
#include <graphic/region.h>
#include <graphic/color.h>
#include <graphic/matrix.h>
#include <graphic/text.h>
#include <graphic/icon.h>
#include <xfs/xfs.h>

struct surface_t;
struct render_t;

/*
 * Each pixel is a 32-bits, with alpha in the upper 8 bits, then red green and blue.
 * The 32-bit quantities are stored native-endian, Pre-multiplied alpha is used.
 * That is, 50% transparent red is 0x80800000 not 0x80ff0000.
 */
struct surface_t
{
	int width;
	int height;
	int stride;
	int pixlen;
	void * pixels;
	struct render_t * r;
	void * rctx;
	void * priv;
};

struct render_t
{
	char * name;
	struct list_head list;

	void * (*create)(struct surface_t * s);
	void (*destroy)(void * rctx);

	void (*blit)(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct surface_t * src);
	void (*fill)(struct surface_t * s, struct region_t * clip, struct matrix_t * m, int w, int h, struct color_t * c);
	void (*text)(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct text_t * txt);
	void (*icon)(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct icon_t * ico);

	void (*shape_line)(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, int thickness, struct color_t * c);
	void (*shape_polyline)(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
	void (*shape_curve)(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
	void (*shape_triangle)(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, struct point_t * p2, int thickness, struct color_t * c);
	void (*shape_rectangle)(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int radius, int thickness, struct color_t * c);
	void (*shape_polygon)(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
	void (*shape_circle)(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int thickness, struct color_t * c);
	void (*shape_ellipse)(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int thickness, struct color_t * c);
	void (*shape_arc)(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int a1, int a2, int thickness, struct color_t * c);
};

static inline int surface_get_width(struct surface_t * s)
{
	return s->width;
}

static inline int surface_get_height(struct surface_t * s)
{
	return s->height;
}

static inline int surface_get_stride(struct surface_t * s)
{
	return s->stride;
}

static inline void * surface_get_pixels(struct surface_t * s)
{
	return s->pixels;
}

static inline void surface_blit(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct surface_t * src)
{
	s->r->blit(s, clip, m, src);
}

static inline void surface_fill(struct surface_t * s, struct region_t * clip, struct matrix_t * m, int w, int h, struct color_t * c)
{
	s->r->fill(s, clip, m, w, h, c);
}

static inline void surface_text(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct text_t * txt)
{
	s->r->text(s, clip, m, txt);
}

static inline void surface_icon(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct icon_t * ico)
{
	s->r->icon(s, clip, m, ico);
}

static inline void surface_shape_line(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, int thickness, struct color_t * c)
{
	s->r->shape_line(s, clip, p0, p1, thickness, c);
}

static inline void surface_shape_polyline(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c)
{
	s->r->shape_polyline(s, clip, p, n, thickness, c);
}

static inline void surface_shape_curve(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c)
{
	s->r->shape_curve(s, clip, p, n, thickness, c);
}

static inline void surface_shape_triangle(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, struct point_t * p2, int thickness, struct color_t * c)
{
	s->r->shape_triangle(s, clip, p0, p1, p2, thickness, c);
}

static inline void surface_shape_rectangle(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int radius, int thickness, struct color_t * c)
{
	s->r->shape_rectangle(s, clip, x, y, w, h, radius, thickness, c);
}

static inline void surface_shape_polygon(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c)
{
	s->r->shape_polygon(s, clip, p, n, thickness, c);
}

static inline void surface_shape_circle(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int thickness, struct color_t * c)
{
	s->r->shape_circle(s, clip, x, y, radius, thickness, c);
}

static inline void surface_shape_ellipse(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int thickness, struct color_t * c)
{
	s->r->shape_ellipse(s, clip, x, y, w, h, thickness, c);
}

static inline void surface_shape_arc(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int a1, int a2, int thickness, struct color_t * c)
{
	s->r->shape_arc(s, clip, x, y, radius, a1, a2, thickness, c);
}

void * render_default_create(struct surface_t * s);
void render_default_destroy(void * rctx);
void render_default_blit(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct surface_t * src);
void render_default_fill(struct surface_t * s, struct region_t * clip, struct matrix_t * m, int w, int h, struct color_t * c);
void render_default_text(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct text_t * txt);
void render_default_icon(struct surface_t * s, struct region_t * clip, struct matrix_t * m, struct icon_t * ico);
void render_default_shape_line(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, int thickness, struct color_t * c);
void render_default_shape_polyline(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
void render_default_shape_curve(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
void render_default_shape_triangle(struct surface_t * s, struct region_t * clip, struct point_t * p0, struct point_t * p1, struct point_t * p2, int thickness, struct color_t * c);
void render_default_shape_rectangle(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int radius, int thickness, struct color_t * c);
void render_default_shape_polygon(struct surface_t * s, struct region_t * clip, struct point_t * p, int n, int thickness, struct color_t * c);
void render_default_shape_circle(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int thickness, struct color_t * c);
void render_default_shape_ellipse(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int thickness, struct color_t * c);
void render_default_shape_arc(struct surface_t * s, struct region_t * clip, int x, int y, int radius, int a1, int a2, int thickness, struct color_t * c);

struct render_t * search_render(void);
bool_t register_render(struct render_t * r);
bool_t unregister_render(struct render_t * r);
struct surface_t * surface_alloc(int width, int height, void * priv);
struct surface_t * surface_alloc_from_xfs(struct xfs_context_t * ctx, const char * filename);
struct surface_t * surface_alloc_from_buf(const void * buf, int len);
struct surface_t * surface_alloc_qrcode(const char * txt, int pixsz);
void surface_free(struct surface_t * s);

struct surface_t * surface_clone(struct surface_t * s, int x, int y, int w, int h, int r);
struct surface_t * surface_extend(struct surface_t * s, int width, int height, const char * type);
void surface_clear(struct surface_t * s, struct color_t * c, int x, int y, int w, int h);
void surface_set_pixel(struct surface_t * s, int x, int y, struct color_t * c);
void surface_get_pixel(struct surface_t * s, int x, int y, struct color_t * c);

void surface_effect_glass(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int radius);
void surface_effect_shadow(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, int radius, struct color_t * c);
void surface_effect_gradient(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h, struct color_t * lt, struct color_t * rt, struct color_t * rb, struct color_t * lb);
void surface_effect_checkerboard(struct surface_t * s, struct region_t * clip, int x, int y, int w, int h);
void surface_filter_gray(struct surface_t * s);
void surface_filter_sepia(struct surface_t * s);
void surface_filter_invert(struct surface_t * s);
void surface_filter_coloring(struct surface_t * s, struct color_t * c);
void surface_filter_hue(struct surface_t * s, int angle);
void surface_filter_saturate(struct surface_t * s, int saturate);
void surface_filter_brightness(struct surface_t * s, int brightness);
void surface_filter_contrast(struct surface_t * s, int contrast);
void surface_filter_opacity(struct surface_t * s, int alpha);
void surface_filter_haldclut(struct surface_t * s, struct surface_t * clut, const char * type);
void surface_filter_blur(struct surface_t * s, int radius);

#ifdef __cplusplus
}
#endif

#endif /* __GRAPHIC_SURFACE_H__ */
