const XORIGIN=160;
const YORIGIN=100;
const PARALELL=0;
const PERSPECTIVE=1;

struct vertex_type {

    long lx,ly,lz,lt;
    long wx,wy,wz,wt;
    long ax,ay,az,at;
    long sx,sy,st;
};

struct polygon_type {
    int number_of_vertices;
    int color;
    int zmax,zmin;
    int xmax,xmin;
    int ymax,ymin;
    vertex_type **vertex;
    int sortflag;
    polygon_type *ptr;
};

struct object_type {
    int number_of_vertices;
    int number_of_polygons;
    int x,yz;
    polygon_type *polygon;
    vertex_type *vertex;
    int convex;
};

struct world_type {
    int number_of_objects;
    object_type *obj;
};

struct polygon_list_type {
    int number_of_polygons;
    polygon_type *ptr;
};

void inittrans();
void scale(float sf);
void rotate(float ax, float ay, float az);
void translate(int xt, int yt, int zt);
void transform(object_type *object);
void project(object_type *object, int distance);
void draw_object(object_type object, char far *screen);
int backface(polygon_type polygon);

