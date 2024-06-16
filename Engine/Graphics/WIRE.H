const XORIGIN = 160;
const YORIGIN = 100;

struct vertex_type {
	int lx,ly,lz,lt;
	int wx,wy,wz,wt;
	int sx,sy,sz,st;
};

struct line_type {
	int start,end;
};

struct shape_type {
	int color;
	int number_of_vertices;
	int number_of_lines;
	vertex_type *vertex;
	line_type *line;
};

void inittrans();
void scale(float sf);
void rotate(float ax, float ay, float az);
void translate(int xt, int yt, int zt);
void transform(shape_type *shape);
void project(shape_type *shape, int distance);
void draw_shape(shape_type shape, char far *screen);