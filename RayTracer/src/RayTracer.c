/*            PURPOSE : Ray tracing framework
 
        PREREQUISITES : matrix.h, affine.h, color.h
 */

#include <X11/Xlib.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

#include "matrix.h"

#define X                1
#define Y                2
#define Z                3

#define INFINITE_PLANE   0
#define PLANE            1
#define SPHERE           2

#define EPSILON          0.000001
#define N_OBJECTS        1024
#define MAX_INTENSITY    255.0

#define Ex               5.0
#define Ey               5.0
#define Ez               2.5

#define Gx               0.0
#define Gy               0.0
#define Gz              -1.0

#define UPx              0.0
#define UPy              0.0
#define UPz              1.0

#define Lx               10.0
#define Ly               5.0
#define Lz               5.0

#define Near             1.0
#define Far              25.0

#define THETA            45.0
#define ASPECT           1.5

#define H                800

typedef struct {
    int width, height ;
} window_t ;

typedef struct {
    double r, g, b ;
} color_t ;

typedef struct {
    dmatrix_t UP ;
    dmatrix_t E ;
    dmatrix_t G ;
    dmatrix_t u, v, n ;
} camera_t ;

typedef struct {
    int type ;
    double (*intersection)(dmatrix_t *, dmatrix_t *) ;
    dmatrix_t *(*normal)(dmatrix_t *) ;
    dmatrix_t M, Minv ;
    color_t specular_color, diffuse_color, ambient_color ;
    double density, reflectivity, specular_coeff, diffuse_coeff, ambient_coeff, f ;
} object_t ;

typedef struct {
    dmatrix_t position ;
    color_t color ;
    color_t intensity ;
} light_t ;

static object_t object[N_OBJECTS] ;
int nobjects = 0 ;

Display *InitX(Display *d, Window *w, int *s, window_t *Window) {
    
    d = XOpenDisplay(NULL) ;
    if(d == NULL) {
        printf("Cannot open display\n") ;
        exit(1) ;
    }
    *s = DefaultScreen(d) ;
    *w = XCreateSimpleWindow(d,RootWindow(d,*s),0,0,Window->width,Window->height,1,BlackPixel(d,*s),WhitePixel(d, *s)) ;
    Atom delWindow = XInternAtom(d,"WM_DELETE_WINDOW",0) ;
    XSetWMProtocols(d,*w,&delWindow,1) ;
    XSelectInput(d,*w,ExposureMask | KeyPressMask) ;
    XMapWindow(d,*w) ;
    return(d) ;
}

void SetCurrentColorX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
    
    XSetForeground(d,*gc,r << 16 | g << 8 | b) ;
}

void SetPixelX(Display *d, Window w, int s, int i, int j) {
    
    XDrawPoint(d,w,DefaultGC(d,s),i,j) ;
}

void QuitX(Display *d, Window w) {
    
    XDestroyWindow(d,w) ;
    XCloseDisplay(d) ;
}

dmatrix_t *rotate(double Vx, double Vy, double Vz, double angle) 

{ dmatrix_t *I, *J, *V ;

  I = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
  J = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
  V = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;

  dmat_alloc(I,3,3) ;
  dmat_alloc(J,3,3) ;
  dmat_alloc(V,3,1) ;

  I = dmat_identity(I) ;
  J = dmat_init(J,0.0) ;

  (*V).m[1][1] = Vx ;
  (*V).m[2][1] = Vy ;
  (*V).m[3][1] = Vz ;

  V = dmat_normalize(V) ;

  (*J).m[2][3] = -(*V).m[1][1] ;
  (*J).m[3][2] = (*V).m[1][1] ;
 
  (*J).m[1][3] = (*V).m[2][1] ;
  (*J).m[3][1] = -(*V).m[2][1] ;

  (*J).m[1][2] = -(*V).m[3][1] ;
  (*J).m[2][1] = (*V).m[3][1] ;

  return to_homogeneous(dmat_add(I,dmat_add(dmat_scalar_mult(J,sin(angle)),dmat_scalar_mult(dmat_mult(J,J),1.0 - cos(angle)))),1.0) ;
}

dmatrix_t *translate(double Tx, double Ty, double Tz)

{ dmatrix_t *T ;

  T = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
  dmat_alloc(T,4,4) ;

  T = dmat_identity(T) ;

  (*T).m[1][4] = Tx ;
  (*T).m[2][4] = Ty ;
  (*T).m[3][4] = Tz ;

  return T ;
}

dmatrix_t *scale(double Sx, double Sy, double Sz)

{ dmatrix_t *S ;

  S = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
  dmat_alloc(S,4,4) ;

  S = dmat_identity(S) ;

  (*S).m[1][1] = Sx ;
  (*S).m[2][2] = Sy ;
  (*S).m[3][3] = Sz ;

  return S ;
}

color_t color_init(double r, double g, double b) {
    
    color_t s ;
    
    s.r = r ;
    s.g = g ;
    s.b = b ;
    
    return s ;
}

color_t color_mult(double a, color_t c) {
    
    color_t s ;
    
    s.r = a*c.r ;
    s.g = a*c.g ;
    s.b = a*c.b ;
    
    return s ;
}

color_t color_add(color_t c1, color_t c2) {
    
    color_t s ;
    
    s.r = c1.r + c2.r ;
    s.g = c1.g + c2.g ;
    s.b = c1.b + c2.b ;
    
    return s ;
}

light_t *build_light(light_t *light, dmatrix_t *position, color_t color, color_t intensity) {
    
    dmat_alloc(&light->position,4,1) ;
    
    light->position = *position ;
    light->color.r = color.r ;
    light->color.g = color.g ;
    light->color.b = color.b ;
    light->intensity.r = intensity.r ;
    light->intensity.g = intensity.g ;
    light->intensity.b = intensity.b ;
    return light ;
}

window_t *build_window(window_t *Window, int height, float aspect) {
    
    Window->height = height ;
    Window->width =  aspect*height ;
    
    return(Window) ;
}

camera_t *build_camera(camera_t *Camera, window_t *Window) {
    
    dmat_alloc(&Camera->E,4,1) ;

    Camera->E.m[X][1] = Ex ;
    Camera->E.m[Y][1] = Ey ;
    Camera->E.m[Z][1] = Ez ;
    Camera->E.m[4][1] = 1.0 ;
    
    dmat_alloc(&Camera->G,4,1) ;
    
    Camera->G.m[X][1] = Gx ;
    Camera->G.m[Y][1] = Gy ;
    Camera->G.m[Z][1] = Gz ;
    Camera->G.m[4][1] = 1.0 ;

    dmat_alloc(&Camera->n,4,1) ;
    Camera->n = *dmat_normalize(dmat_sub(&Camera->E,&Camera->G)) ;
    Camera->n.l = 3 ;
    
    dmat_alloc(&Camera->UP,4,1) ;
    
    Camera->UP.l = 3 ;
    
    Camera->UP.m[X][1] = UPx ;
    Camera->UP.m[Y][1] = UPy ;
    Camera->UP.m[Z][1] = UPz ;
    Camera->UP.m[4][1] = 1.0 ;
    
    dmat_alloc(&Camera->u,4,1) ;
    
    Camera->u = *dmat_normalize(dcross_product(&Camera->UP,&Camera->n)) ;
    Camera->v = *dmat_normalize(dcross_product(&Camera->n,&Camera->u)) ;
    
    return(Camera) ;
}

dmatrix_t *intersection_coordinates(dmatrix_t *e, dmatrix_t *direction, double t) {
    
    dmatrix_t *intersection ;
    
    intersection = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(intersection,4,1) ;
    
    intersection->m[X][1] = e->m[X][1] + direction->m[X][1]*t ;
    intersection->m[Y][1] = e->m[Y][1] + direction->m[Y][1]*t ;
    intersection->m[Z][1] = e->m[Z][1] + direction->m[Z][1]*t ;
    intersection->m[4][1] = 1.0 ;
    
    return intersection ;
}

double infinite_plane_intersection(dmatrix_t *e, dmatrix_t *d) {
    
    double t ;
    
    if (fabs(d->m[Z][1]) < EPSILON) {
        t = -1.0 ;
    }
    else {
        t = -e->m[Z][1]/d->m[Z][1] ;
        if (t <= 0.0) {
            t = -1.0 ;
        }
        else {
            t = -1.0*e->m[Z][1]/d->m[Z][1] ;
        }
    }
    return t ;
}

double plane_intersection(dmatrix_t *e, dmatrix_t *d) {
    
    double t ;
    dmatrix_t *intersection ;
    
    if (fabs(d->m[Z][1]) < EPSILON) {
        t = -1.0 ;
    }
    else {
        t = -e->m[Z][1]/d->m[Z][1] ;
        if (t <= 0.0) {
            t = -1.0 ;
        }
        else {
            intersection = intersection_coordinates(e,d,t) ;
            if ((fabs(intersection->m[X][1]) > 1.0) || (fabs(intersection->m[Y][1]) > 1.0)) {
                t = -1.0 ;
            }
            delete_dmatrix(intersection) ;
        }
    }
    return t ;
}

double solve_quadratic(double a, double b, double c) {
    
    double discriminant, t1, t2, min ;
    
    discriminant = b*b - a*c ;
    if (discriminant < 0.0) {
        return -1.0 ;
    }
    else {
        if (discriminant < EPSILON) {
            return -b/a ;
        }
        else {
            t1 = -b/a - sqrtl(discriminant)/a ;
            t2 = -b/a + sqrtl(discriminant)/a ;
 
            if (t1 < t2) {
              min = t1 ; 
            }
            else { 
              min = t2 ;
            }

            if (min > EPSILON) {
              return min ;
            }
            else {
              return -1.0 ;
            }
        }
    }
}

double sphere_intersection(dmatrix_t *e, dmatrix_t *d) {
    
    double a = ddot_product(from_homogeneous(d),from_homogeneous(d)) ;
    double b = ddot_product(from_homogeneous(e),from_homogeneous(d)) ;
    double c = ddot_product(from_homogeneous(e),from_homogeneous(e)) - 1.0 ;
    
    return solve_quadratic(a,b,c) ;
}

dmatrix_t *sphere_normal(dmatrix_t *intersection) {

    dmatrix_t *normal ;

    normal = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(normal,4,1) ;

    normal->m[X][1] = intersection->m[X][1] ;
    normal->m[Y][1] = intersection->m[Y][1] ;
    normal->m[Z][1] = intersection->m[Z][1] ;
    normal->m[4][1] = 0.0 ;
 
    return dmat_normalize(normal) ;
}

dmatrix_t *plane_normal(dmatrix_t *intersection) {

    dmatrix_t *normal ;

    normal = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(normal,4,1) ;

    normal->m[X][1] = 0.0 ;
    normal->m[Y][1] = 0.0 ;
    normal->m[Z][1] = 1.0 ;
    normal->m[4][1] = 0.0 ;
 
    return dmat_normalize(normal) ;
}

int find_min_hit_time(double t0[N_OBJECTS]) {
    
    double min_t = DBL_MAX ;
    int position = -1 ;
  
    for(int i = 0 ; i < nobjects ; i++) {
        if (t0[i] != -1.0) {
            if (t0[i] < min_t) {
                min_t = t0[i] ;
                position = i ;
            }
        }
    }
    return position ;
}

dmatrix_t *ray_direction(camera_t *Camera, window_t *Window, double height, double width, double i, double j) {
   
    int k ; 
    dmatrix_t *d ;
   
    d = (dmatrix_t *)malloc(sizeof(dmatrix_t)) ;
    dmat_alloc(d,3,1) ;

    for (k = 1 ; k <= 3 ; k++) { 
        d->m[k][1] = -1.0*Near*Camera->n.m[k][1] + width*(2.0*i/Window->width - 1.0)*Camera->u.m[k][1] + height*(2.0*j/Window->height - 1.0)*Camera->v.m[k][1] ;
    }

    dmatrix_t* ret = to_homogeneous(d,0.0);
    delete_dmatrix(d);
    return ret; 
}

dmatrix_t *vector_to_light_source(dmatrix_t *intersection, dmatrix_t *light_position) {
    
    return dmat_normalize(dmat_sub(light_position,intersection)) ;
}

dmatrix_t *vector_to_center_of_projection(dmatrix_t *intersection, dmatrix_t *e) {
    
    return dmat_normalize(dmat_sub(e,intersection)) ;
}

dmatrix_t *vector_to_specular_reflection(dmatrix_t *N, dmatrix_t *S) {
    
    return dmat_normalize(dmat_add(dmat_scalar_mult(S,-1.0),dmat_scalar_mult(N,2.0*ddot_product(N,S)))) ;
}

int shadowed(dmatrix_t *e, dmatrix_t *d) {

  int h, k ;
  double t0[N_OBJECTS] ;

    for (k = 0 ; k < nobjects ; k++) {
        t0[k] = (object[k].intersection)(dmat_mult(&object[k].Minv,e),dmat_normalize(dmat_mult(&object[k].Minv,d))) ;
    }
    h = find_min_hit_time(t0) ;
    return h != -1 ;
}

color_t shade(light_t *light, object_t *object, dmatrix_t *e, dmatrix_t *d, color_t color, color_t background, int level) {

color.r = 0.0 ;
color.g = 0.0 ;
color.r = 0.0 ;

return color ;

}

object_t *build_object(int object_type, dmatrix_t *M, color_t ambient_color, color_t diffuse_color, color_t specular_color, double ambient_coeff, double diffuse_coeff, double specular_coeff, double f, double reflectivity) {
    
    object_t *object ;
    
    object = malloc(sizeof(*object)) ;
    object->type = object_type ;

    dmat_alloc(&object->M,4,4) ;
    object->M = *dmat_duplicate(M) ;

    dmat_alloc(&object->Minv,4,4) ;
    object->Minv = *dmat_inverse(&object->M) ;

    object->specular_color = color_init(specular_color.r,specular_color.g,specular_color.b) ;
    object->diffuse_color = color_init(diffuse_color.r,diffuse_color.g,diffuse_color.b) ;
    object->ambient_color = color_init(ambient_color.r,ambient_color.g,ambient_color.b) ;

    object->specular_coeff = specular_coeff ;
    object->diffuse_coeff = diffuse_coeff ;
    object->ambient_coeff = ambient_coeff ;

    object->f = f ;
    object->reflectivity = reflectivity ;
    
    switch (object_type) {
            
        case SPHERE :
            
            object->intersection = &sphere_intersection ;
            object->normal = &sphere_normal ;
            break ;
            
        case PLANE :
            object->intersection = &plane_intersection ;
            object->normal = &plane_normal ;
            break ;
            
        case INFINITE_PLANE :
            
            object->intersection = &infinite_plane_intersection ;
            object->normal = &plane_normal ;
            break ;
        
        default :
            break ;
            
    }
    nobjects++ ;
    return(object) ;
}

int main() {
    
    Display *d ;
    Window w ;
    XEvent e ;
    
    int i, j, s ;
    
    camera_t Camera ;
    window_t Window ;
    light_t light ;
    dmatrix_t M, light_position ;
    color_t pixel, background, light_intensity, light_color, ambient_color, diffuse_color, specular_color ;
    double height, width, aspect, ambient_coeff, diffuse_coeff, specular_coeff, f, reflectivity ;
    
    /* Set the background color */
    
    background = color_init(0.0,0.0,0.0) ;
 
    /* Set up light position, intensity, and color */
    
    dmat_alloc(&light_position,4,1) ;
    
    light_position.m[X][1] = Lx ;
    light_position.m[Y][1] = Ly ;
    light_position.m[Z][1] = Lz ;
    light_position.m[4][1] = 1.0 ;
    
    light_intensity = color_init(1.0,1.0,1.0) ;
    light_color = color_init(1.0,1.0,1.0) ; 
    light = *build_light(&light,&light_position,light_color,light_intensity) ;
    
    /* Build display window and synthetic camera */
    
    Window = *build_window(&Window,H,ASPECT) ;
    Camera = *build_camera(&Camera,&Window) ;
   
    /* Build a sphere */
 
    M  = *translate(0.0,0.0,0.0) ;
    
    specular_color = color_init(1.0,1.0,1.0) ;
    diffuse_color = color_init(0.0,0.0,1.0) ;
    ambient_color = color_init(0.0,0.0,1.0) ;
    
    specular_coeff = 0.4 ;
    diffuse_coeff = 0.4 ;
    ambient_coeff = 0.2 ;

    f = 10.0 ;
    reflectivity = 0.0 ;

    object[nobjects] = *build_object(SPHERE,&M,ambient_color,diffuse_color,specular_color,ambient_coeff,diffuse_coeff,specular_coeff,f,reflectivity) ;
    
    aspect = ASPECT ; /* Set near plane dimensions */
    height = Near*tan(M_PI/180.0 * THETA/2.0) ;
    width = height*aspect ;
    
    dmatrix_t *direction ;
    
    d = InitX(d,&w,&s,&Window) ;
    XNextEvent(d, &e) ;
    
    while (1) {
        XNextEvent(d,&e) ;
        if (e.type == Expose) {
            for (i = 0 ; i < Window.width ; i++) {
                for (j = 0  ; j < Window.height ; j++) {
                    direction = ray_direction(&Camera,&Window,height,width,(double)i,(double)j) ;
                    pixel = shade(&light,object,&Camera.E,direction,pixel,background,3) ;
                    SetCurrentColorX(d,&(DefaultGC(d,s)),(int)pixel.r,(int)pixel.g,(int)pixel.b) ;
                    SetPixelX(d,w,s,i,Window.height - (j + 1)) ;
                    delete_dmatrix(direction) ;
                }
            }
        }
        if (e.type == KeyPress)
            break ;
        if (e.type == ClientMessage)
            break ;
    }
    QuitX(d,w) ;
}
