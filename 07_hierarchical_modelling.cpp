#include <math.h>   

#include "07_hierarchical_modelling.hpp"
#include "texture.hpp"

GLuint shaderProgram;
GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 c_translation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;


//----------------------------declarations-------------------------

const int num_vertices = 36;
const int num_vertices_box = 84;
float length=100,width=50,height=10,thickness=2;
float roomlength = 1000, roomheight = 1000, roomdepth = 1000;
float wallthickness = 10;
float doorlength = 200, doorheight = 400, doorthickness = 10;
float windowlength = 150, windowheight = 150, windowthickness = 10;
int tri_idx=0;
int room_idx=0;
int num_frames;
double timer = 1.0/24;

float wsize = 1000.0;
glm::vec4 v_positions_box[num_vertices_box];
glm::vec4 v_colors_box[num_vertices_box];
glm::vec4 v_normals_box[num_vertices_box];

glm::vec4 roomcolor = glm::vec4(0.2, 0.4, 0.5, 1.0);
glm::vec4 roomcolorinner = glm::vec4(0.9, 0.4, 0.6, 1.0);
glm::vec4 doorcolor = glm::vec4(0.5, 0.2, 0.4, 1.0);
glm::vec4 windowcolor = glm::vec4(0.5, 0.3, 0.2, 1.0);

glm::vec4 hiplpos[390960];
glm::vec4 hiplcol[390960];

glm::vec4 hiprpos[390960];
glm::vec4 hiprcol[390960];

glm::vec4 headpos[388800];
glm::vec4 headcol[388800];

glm::vec4 neckpos[388800];
glm::vec4 neckcol[388800];

glm::vec4 torso1pos[390960];
glm::vec4 torso1col[390960];

glm::vec4 torso2pos[390960];
glm::vec4 torso2col[390960];

glm::vec4 torso3pos[390960];
glm::vec4 torso3col[390960];

glm::vec4 thighlpos[390960];
glm::vec4 thighlcol[390960];

glm::vec4 thighrpos[390960];
glm::vec4 thighrcol[390960];

glm::vec4 kneelpos[388800];
glm::vec4 kneelcol[388800];

glm::vec4 kneerpos[388800];
glm::vec4 kneercol[388800];

glm::vec4 leglpos[390960];
glm::vec4 leglcol[390960];

glm::vec4 legrpos[390960];
glm::vec4 legrcol[390960];

glm::vec4 footlpos[388800];
glm::vec4 footlcol[388800];

glm::vec4 footrpos[388800];
glm::vec4 footrcol[388800];

glm::vec4 shoulderlpos[388800];
glm::vec4 shoulderlcol[388800];

glm::vec4 shoulderrpos[388800];
glm::vec4 shoulderrcol[388800];

glm::vec4 uarmlpos[390960];
glm::vec4 uarmlcol[390960];

glm::vec4 uarmrpos[390960];
glm::vec4 uarmrcol[390960];

glm::vec4 elbowlpos[388800];
glm::vec4 elbowlcol[388800];

glm::vec4 elbowrpos[388800];
glm::vec4 elbowrcol[388800];

glm::vec4 larmlpos[390960];
glm::vec4 larmlcol[390960];

glm::vec4 larmrpos[390960];
glm::vec4 larmrcol[390960];

glm::vec4 handlpos[388800];
glm::vec4 handlcol[388800];

glm::vec4 handrpos[388800];
glm::vec4 handrcol[388800];

/// ------ props ------

glm::vec4 hatcol[390960];
glm::vec4 hatpos[390960];

glm::vec4 umbrellastickcol[390960];
glm::vec4 umbrellastickpos[390960];

glm::vec4 umbrellafoldedcol[390960];
glm::vec4 umbrellafoldedpos[390960];

glm::vec4 umbrellaopencol[388800];
glm::vec4 umbrellaopenpos[388800];

//-----------------dog delcarations----------

glm::vec4 dogtrunkpos[388800];  // ellipse
glm::vec4 dogtrunkcol[388800];

glm::vec4 dogheadpos[388800];   // ellipse
glm::vec4 dogheadcol[388800];

glm::vec4 dogneckpos[390960];   //  frustom
glm::vec4 dogneckcol[390960];

glm::vec4 dogtailpos[390960];   // frustom
glm::vec4 dogtailcol[390960];

glm::vec4 dogarm1pos[390960];   // frustom
glm::vec4 dogarm1col[390960];

glm::vec4 dogarm2pos[390960];   // frustom
glm::vec4 dogarm2col[390960];

glm::vec4 dogarm3pos[390960];   // frustom
glm::vec4 dogarm3col[390960];

glm::vec4 dogarm4pos[390960];   // frustom
glm::vec4 dogarm4col[390960];

glm::vec4 roompos[174];   // room
glm::vec4 roomcol[174];
glm::vec2 tex_coords[174];
glm::vec4 roomnormal[174];



//--------------furniture declarations--------------

glm::vec4 tabletoppos[36];
glm::vec4 tabletopcol[36];
glm::vec2 tabletoptex[36];


glm::vec4 tableleg1pos[36];
glm::vec4 tableleg1col[36];
// glm::vec4 tableleg1tex[36];
glm::vec4 tableleg2pos[36];
glm::vec4 tableleg2col[36];
// glm::vec4 tableleg2tex[36];
glm::vec4 tableleg3pos[36];
glm::vec4 tableleg3col[36];
// glm::vec4 tableleg3tex[36];
glm::vec4 tableleg4pos[36];
glm::vec4 tableleg4col[36];
// glm::vec4 tableleg4tex[36];


glm::vec4 lampbasepos[390960];   //  frustom
glm::vec4 lampbasecol[390960];
glm::vec4 lamptrunkpos[390960];   //  frustom
glm::vec4 lamptrunkcol[390960];
glm::vec4 lamptoppos[390960];   //  frustom
glm::vec4 lamptopcol[390960];
glm::vec2 lamptoptex[390960];


glm::vec4 stooltoppos[390960];   //  frustom
glm::vec4 stooltopcol[390960];
glm::vec2 stooltoptex[390960];

glm::vec4 stoolleg1pos[390960];
glm::vec4 stoolleg1col[390960];
glm::vec4 stoolleg2pos[390960];
glm::vec4 stoolleg2col[390960];
glm::vec4 stoolleg3pos[390960];
glm::vec4 stoolleg3col[390960];
glm::vec4 stoolleg4pos[390960];
glm::vec4 stoolleg4col[390960];


glm::vec4 cupboardpos[36];
glm::vec4 cupboardcol[36];
glm::vec2 cupboardtex[36];


glm::vec4 chairbasepos[36];
glm::vec4 chairbasecol[36];
glm::vec2 chairbasetex[36];
glm::vec4 chairbackpos[36];
glm::vec4 chairbackcol[36];
glm::vec2 chairbacktex[36];

glm::vec4 chairleg1pos[390960];   //  frustom
glm::vec4 chairleg1col[390960];
glm::vec4 chairleg2pos[390960];   //  frustom
glm::vec4 chairleg2col[390960];
glm::vec4 chairleg3pos[390960];   //  frustom
glm::vec4 chairleg3col[390960];
glm::vec4 chairleg4pos[390960];   //  frustom
glm::vec4 chairleg4col[390960];


glm::vec4 framepos[36];
glm::vec4 framecol[36];
glm::vec2 frametex[36];

// -----------------normals declarations-------------------------------
glm::vec4 hiplnormal[390960];

glm::vec4 hiprnormal[390960];

glm::vec4 headnormal[388800];

glm::vec4 necknormal[388800];

glm::vec4 torso1normal[390960];

glm::vec4 torso2normal[390960];

glm::vec4 torso3normal[390960];

glm::vec4 thighlnormal[390960];

glm::vec4 thighrnormal[390960];

glm::vec4 kneelnormal[388800];

glm::vec4 kneernormal[388800];

glm::vec4 leglnormal[390960];

glm::vec4 legrnormal[390960];

glm::vec4 footlnormal[388800];

glm::vec4 footrnormal[388800];

glm::vec4 shoulderlnormal[388800];

glm::vec4 shoulderrnormal[388800];

glm::vec4 uarmlnormal[390960];

glm::vec4 uarmrnormal[390960];

glm::vec4 elbowlnormal[388800];

glm::vec4 elbowrnormal[388800];

glm::vec4 larmlnormal[390960];

glm::vec4 larmrnormal[390960];

glm::vec4 handlnormal[388800];

glm::vec4 handrnormal[388800];

/// ------ props ------

glm::vec4 hatnormal[390960];

glm::vec4 umbrellasticknormal[390960];

glm::vec4 umbrellafoldednormal[390960];

glm::vec4 umbrellaopennormal[388800];

//-----------------dog delcarations----------

glm::vec4 dogtrunknormal[388800];  // ellipse

glm::vec4 dogheadnormal[388800];   // ellipse

glm::vec4 dognecknormal[390960];   //  frustom

glm::vec4 dogtailnormal[390960];   // frustom

glm::vec4 dogarm1normal[390960];   // frustom

glm::vec4 dogarm2normal[390960];   // frustom

glm::vec4 dogarm3normal[390960];   // frustom

glm::vec4 dogarm4normal[390960];   // frustom


//--------------furniture declarations--------------

glm::vec4 tabletopnormal[36];

glm::vec4 tableleg1normal[36];
glm::vec4 tableleg2normal[36];
glm::vec4 tableleg3normal[36];
glm::vec4 tableleg4normal[36];


glm::vec4 lampbasenormal[390960];   //  frustom
glm::vec4 lamptrunknormal[390960];   //  frustom
glm::vec4 lamptopnormal[390960];   //  frustom


glm::vec4 stooltopnormal[390960];   //  frustom

glm::vec4 stoolleg1normal[390960];
glm::vec4 stoolleg2normal[390960];
glm::vec4 stoolleg3normal[390960];
glm::vec4 stoolleg4normal[390960];


glm::vec4 cupboardnormal[36];


glm::vec4 chairbasenormal[36];
glm::vec4 chairbacknormal[36];

glm::vec4 chairleg1normal[390960];   //  frustom
glm::vec4 chairleg2normal[390960];   //  frustom
glm::vec4 chairleg3normal[390960];   //  frustom
glm::vec4 chairleg4normal[390960];   //  frustom


glm::vec4 framenormal[36];

//------------------------declarations end-----------------------


//---------------------------- functions to build shapes -------------------------------------

glm::vec4 positionsRoom[32] = {

  glm::vec4(0.0, 0.0,0.0, 1.0),
  glm::vec4(roomlength, 0.0,0.0, 1.0),
  glm::vec4(0.0, 0.0, roomdepth, 1.0),
  glm::vec4(roomlength, 0.0, roomdepth, 1.0),

  glm::vec4(0.0, roomheight,0.0, 1.0),
  glm::vec4(roomlength, roomheight,0.0, 1.0),
  glm::vec4(0.0, roomheight, roomdepth, 1.0),
  glm::vec4(roomlength, roomheight, roomdepth, 1.0),

  glm::vec4(0.0+wallthickness, 0.0,0.0+wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, 0.0,0.0+wallthickness, 1.0),
  glm::vec4(0.0+wallthickness, 0.0, roomdepth-wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, 0.0, roomdepth-wallthickness, 1.0),

  glm::vec4(0.0+wallthickness, roomheight-wallthickness,0.0+wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, roomheight-wallthickness,0.0+wallthickness, 1.0),
  glm::vec4(0.0+wallthickness, roomheight-wallthickness, roomdepth-wallthickness, 1.0),
  glm::vec4(roomlength-wallthickness, roomheight-wallthickness, roomdepth-wallthickness, 1.0),

  glm::vec4((roomlength-doorlength)/2.0, 0.0,0.0, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, 0.0,0.0, 1.0),
  glm::vec4((roomlength-doorlength)/2.0, doorheight,0.0, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, doorheight,0.0, 1.0),

  glm::vec4((roomlength-doorlength)/2.0, 0.0,doorthickness, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, 0.0,doorthickness, 1.0),
  glm::vec4((roomlength-doorlength)/2.0, doorheight,doorthickness, 1.0),
  glm::vec4((roomlength+doorlength)/2.0, doorheight,doorthickness, 1.0),

  glm::vec4(roomlength, (roomheight-windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight-windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight+windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength, (roomheight+windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),

  glm::vec4(roomlength-windowthickness, (roomheight-windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight-windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight+windowheight)/2.0, (roomdepth-windowlength)/2.0, 1.0),
  glm::vec4(roomlength-windowthickness, (roomheight+windowheight)/2.0, (roomdepth+windowlength)/2.0, 1.0),

};

glm::vec4 colorsRoom[32] = {

  roomcolor,
  roomcolor,
  roomcolor,
  roomcolor,

  roomcolor,
  roomcolor,
  roomcolor,
  roomcolor,

  roomcolorinner,
  roomcolorinner,
  roomcolorinner,
  roomcolorinner,


  roomcolorinner,
  roomcolorinner,
  roomcolorinner,
  roomcolorinner,

  doorcolor,
  doorcolor,
  doorcolor,
  doorcolor,

  doorcolor,
  doorcolor,
  doorcolor,
  doorcolor,

  windowcolor,
  windowcolor,
  windowcolor,
  windowcolor,

  windowcolor,
  windowcolor,
  windowcolor,
  windowcolor,

};

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};



glm::vec4 positionsBox[16] = {

  glm::vec4(0.0, 0.0,0.0-height, 1.0),
  glm::vec4(length, 0.0,0.0-height, 1.0),
  glm::vec4(length, width,0.0-height, 1.0),
  glm::vec4(0.0, width,0.0-height, 1.0),

  glm::vec4(0.0, 0.0,0.0, 1.0),
  glm::vec4(length, 0.0,0.0, 1.0),
  glm::vec4(length, width,0.0, 1.0),
  glm::vec4(0.0, width,0.0, 1.0),

  glm::vec4(0.0+thickness, 0.0+thickness,0.0+thickness-height, 1.0),
  glm::vec4(length-thickness, 0.0+thickness,0.0+thickness-height, 1.0),
  glm::vec4(length-thickness, width-thickness,0.0+thickness-height, 1.0),
  glm::vec4(0.0+thickness, width-thickness,0.0+thickness-height, 1.0),

  glm::vec4(0.0+thickness, 0.0+thickness,0.0, 1.0),
  glm::vec4(length-thickness, 0.0+thickness,0.0, 1.0),
  glm::vec4(length-thickness, width-thickness,0.0, 1.0),
  glm::vec4(0.0+thickness, width-thickness,0.0, 1.0),
};


glm::vec4 colorsBox[16] = {
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.5, 0.2, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.8, 0.3, 0.0, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.7, 0.0, 0.8, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
  glm::vec4(0.5, 0.0, 0.5, 1.0),
 
};


void quad_box(int a, int b, int c, int d)
{
  v_colors_box[tri_idx] = colorsBox[a]; v_positions_box[tri_idx] = positionsBox[a] ;v_normals_box[tri_idx] = positionsBox[a]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[b]; v_positions_box[tri_idx] = positionsBox[b] ;v_normals_box[tri_idx] = positionsBox[b]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[c]; v_positions_box[tri_idx] = positionsBox[c] ;v_normals_box[tri_idx] = positionsBox[c]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[a]; v_positions_box[tri_idx] = positionsBox[a] ;v_normals_box[tri_idx] = positionsBox[a]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[c]; v_positions_box[tri_idx] = positionsBox[c] ;v_normals_box[tri_idx] = positionsBox[c]; tri_idx++;
  v_colors_box[tri_idx] = colorsBox[d]; v_positions_box[tri_idx] = positionsBox[d] ;v_normals_box[tri_idx] = positionsBox[d]; tri_idx++;
 }



void colorbox(void)
{
    quad_box( 1, 0, 3, 2 );
    quad_box( 2, 3, 7, 6 );
    quad_box( 3, 0, 4, 7 );
    quad_box( 6, 5, 1, 2 );
    // quad_box( 4, 5, 6, 7 );
    quad_box( 5, 4, 0, 1 );
    quad_box( 9, 8, 11, 10 );
    quad_box( 10, 11, 15, 14 );
    quad_box( 11, 8, 12, 15 );
    quad_box( 14, 13, 9, 10 );
    // quad_box( 12, 13, 14, 15 );
    quad_box( 13, 12, 8, 9 );
    quad_box( 4, 12, 13, 5 );
    quad_box( 5, 13, 14, 6 );
    quad_box( 6, 14, 15, 7 );
    quad_box( 7, 15, 12, 4 );
}

void room_quad_box(int a, int b, int c, int d)
{
  roomcol[room_idx] = colorsRoom[a]; roompos[room_idx] = positionsRoom[a]; tex_coords[room_idx] = t_coords[1]; room_idx++;
  roomcol[room_idx] = colorsRoom[b]; roompos[room_idx] = positionsRoom[b]; tex_coords[room_idx] = t_coords[3]; room_idx++;
  roomcol[room_idx] = colorsRoom[c]; roompos[room_idx] = positionsRoom[c]; tex_coords[room_idx] = t_coords[0]; room_idx++;
  roomcol[room_idx] = colorsRoom[b]; roompos[room_idx] = positionsRoom[b]; tex_coords[room_idx] = t_coords[3]; room_idx++;
  roomcol[room_idx] = colorsRoom[c]; roompos[room_idx] = positionsRoom[c]; tex_coords[room_idx] = t_coords[0]; room_idx++;
  roomcol[room_idx] = colorsRoom[d]; roompos[room_idx] = positionsRoom[d]; tex_coords[room_idx] = t_coords[2]; room_idx++;
 }

void room(void)
{
  room_quad_box(0,1,2,3);  
  room_quad_box(4,5,6,7);  
  room_quad_box(12,13,14,15);  
  room_quad_box(2,3,6,7);  
  room_quad_box(10,11,14,15);  
  room_quad_box(0,2,4,6);
  room_quad_box(8,10,12,14);

  room_quad_box(0,16,4,18);
  room_quad_box(18,4,19,5);
  room_quad_box(19,5,17,1);

  room_quad_box(8,20,12,22);  
  room_quad_box(22,12,23,13);
  room_quad_box(23,13,21,9);

  room_quad_box(16,20,18,22);
  room_quad_box(18,22,19,23);
  room_quad_box(19,23,17,21);

  room_quad_box(1,24,5,26);
  room_quad_box(5,26,7,27);
  room_quad_box(7,27,3,25);
  room_quad_box(3,25,1,24);

  room_quad_box(9,13,30,28);
  room_quad_box(30,31,13,15);
  room_quad_box(15,31,29,11);
  room_quad_box(11,29,9,28);  

  room_quad_box(24,28,26,30);
  room_quad_box(26,30,27,31);
  room_quad_box(27,31,25,29);
  room_quad_box(25,29,24,28);  

}

void tabletoptexfill(void){

  int i=0;
  while(i<36){
    tabletoptex[i] = t_coords[1];i++;
    tabletoptex[i] = t_coords[2];i++;
    tabletoptex[i] = t_coords[0];i++;
    tabletoptex[i] = t_coords[2];i++;
    tabletoptex[i] = t_coords[0];i++;
    tabletoptex[i] = t_coords[3];i++;    
  }
}

void lamptoptexfill(void){

  int i=0;
  while(i<390960){
    lamptoptex[i] = t_coords[1];i++;
    lamptoptex[i] = t_coords[3];i++;
    lamptoptex[i] = t_coords[0];i++;
    lamptoptex[i] = t_coords[3];i++;
    lamptoptex[i] = t_coords[0];i++;
    lamptoptex[i] = t_coords[2];i++;    
  }
}

void stooltoptexfill(void){
  int i=0;
  while(i<390960){
    stooltoptex[i] = t_coords[1];i++;
    stooltoptex[i] = t_coords[3];i++;
    stooltoptex[i] = t_coords[0];i++;
    stooltoptex[i] = t_coords[3];i++;
    stooltoptex[i] = t_coords[0];i++;
    stooltoptex[i] = t_coords[2];i++;    
  }

}

void cupboardtexfill(void){
int i=0;
  while(i<36){
    cupboardtex[i] = t_coords[1];i++;
    cupboardtex[i] = t_coords[3];i++;
    cupboardtex[i] = t_coords[0];i++;
    cupboardtex[i] = t_coords[3];i++;
    cupboardtex[i] = t_coords[0];i++;
    cupboardtex[i] = t_coords[2];i++;    
  }

}

void chairbacktexfill(void){
int i=0;
  while(i<36){
    chairbacktex[i] = t_coords[1];i++;
    chairbacktex[i] = t_coords[3];i++;
    chairbacktex[i] = t_coords[0];i++;
    chairbacktex[i] = t_coords[3];i++;
    chairbacktex[i] = t_coords[0];i++;
    chairbacktex[i] = t_coords[2];i++;    
  }

}

void chairbasetexfill(void){
int i=0;
  while(i<36){
    chairbasetex[i] = t_coords[1];i++;
    chairbasetex[i] = t_coords[3];i++;
    chairbasetex[i] = t_coords[0];i++;
    chairbasetex[i] = t_coords[3];i++;
    chairbasetex[i] = t_coords[0];i++;
    chairbasetex[i] = t_coords[2];i++;    
  }

}

void frametexfill(void){
int i=0;
  while(i<36){
    frametex[i] = t_coords[1];i++;
    frametex[i] = t_coords[3];i++;
    frametex[i] = t_coords[0];i++;
    frametex[i] = t_coords[3];i++;
    frametex[i] = t_coords[0];i++;
    frametex[i] = t_coords[2];i++;    
  }

}
int get_cuboid_size(float l, float w, float h){
  return 36;
}

void cuboid(float l, float w, float h,glm::vec4 vpos[], glm::vec4 npos[]){
  int ind = 0;
  float l2 = l/2.0;
  float w2 = w/2.0;
  float h2 = h/2.0;

  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,w2,-1.0*h2,1.0); npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
  ind++;


  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,h2,1.0); npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
  ind++;


  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,-1.0,0.0,1.0);
  ind++; 


  vpos[ind] = glm::vec4(-1.0*l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(-1.0*l2,w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,w2,h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(-1.0*l2,w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 
  vpos[ind] = glm::vec4(l2,w2,-1.0*h2,1.0);npos[ind] = glm::vec4(0.0,1.0,0.0,1.0);
  ind++; 


  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(-1.0*l2,w2,-1.0*h2,1.0);npos[ind] = glm::vec4(-1.0,0.0,0.0,1.0);
  ind++;

  vpos[ind] = glm::vec4(l2,-1.0*w2,h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,w2,h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,-1.0*w2,-1.0*h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,w2,h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;
  vpos[ind] = glm::vec4(l2,w2,-1.0*h2,1.0);npos[ind] = glm::vec4(1.0,0.0,0.0,1.0);
  ind++;

}


int get_cylinder_size(float height,float radius){
  int lats = 180;
  int longts = 360;
  return 2*longts*3+lats*longts*6;
}

void cylinder(float height,float radius,glm::vec4 vpos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),0.0,1.0);
    ind++;
  }

  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;

    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),(j+1)*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),j*sc,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    ind++;

    }
  }

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(radius*cos(i*M_PI/180),radius*sin(i*M_PI/180),height,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    ind++;
    vpos[ind] = glm::vec4(radius*cos((i+1)*M_PI/180),radius*sin((i+1)*M_PI/180),height,1.0);
    ind++;
  } 

}


int get_frustom_size(float height,float r1, float r2){
  int lats = 180;
  int longts = 360;
  return 2*longts*3+lats*longts*6;
}




void frustom(float height,float r1,float r2,glm::vec4 vpos[],glm::vec4 npos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r1*cos(i*M_PI/180),r1*sin(i*M_PI/180),0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r1*cos((i+1)*M_PI/180),r1*sin((i+1)*M_PI/180),0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;
  }

  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
      float rr1 = r1 - j*((r1-r2)*1.0)/lats;
      float rr2 = r1 - (j+1)*((r1-r2)*1.0)/lats;
    vpos[ind] = glm::vec4(rr1*cos(i*M_PI/180),rr1*sin(i*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;

    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr2*cos((i+1)*M_PI/180),rr2*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;

    }
  }

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r2*cos(i*M_PI/180),r2*sin(i*M_PI/180),height,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2*cos((i+1)*M_PI/180),r2*sin((i+1)*M_PI/180),height,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;
  }

}



int get_ellipse_size(float a1,float a2, float a3){
  float lats = 180;
  int longts = 360;
  return lats*longts*6;
}

void ellipse(double a1,double a3,double a2,glm::vec4 vpos[],glm::vec4 npos[]){
  double lats = 180;
  double sc = a1/lats;
  int longts = 360;
  int n = lats*longts*6;

  int ind = 0;

  for(double i=0;i<lats;i++){

    for(double j=0;j<longts;j++){

      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos(j*M_PI/180)/2,a2*sin(i*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      
      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin(i*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos(j*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      
      vpos[ind] = glm::vec4(a3*sin(i*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin(i*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos(i*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos(j*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin(j*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      
      vpos[ind] = glm::vec4(a3*sin((i+1)*M_PI/180)*cos((j+1)*M_PI/180)/2,a2*sin((i+1)*M_PI/180)*sin((j+1)*M_PI/180)/2,a1/2+a1*cos((i+1)*M_PI/180)/2,1.0);
      npos[ind] = vpos[ind];
      ind++;      

    }
  } 

}



int get_elliptical_frustom_size(float height,float r1a,float r1b,float r2a,float r2b){
  float lats = 180;
  int longts = 360;
  return longts*12;
}

void elliptical_frustom(float height,float r1a,float r1b,float r2a,float r2b,glm::vec4 vpos[],glm::vec4 npos[]){
  float lats = 180;

  int longts = 360;

  int ind = 0;

  for(int i=0;i<longts;i++){
    vpos[ind] = glm::vec4(r1a/2*cos(i*M_PI/180),r1b/2*sin(i*M_PI/180),0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,-1.0,1.0);
    ind++;

    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(0.0,0.0,height,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos((i+1)*M_PI/180),r2b/2*sin((i+1)*M_PI/180),height,1.0);
    npos[ind] = vpos[ind];
    ind++;


    vpos[ind] = glm::vec4(r1a/2*cos(i*M_PI/180),r1b/2*sin(i*M_PI/180),0.0,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    npos[ind] = vpos[ind];
    ind++;

    vpos[ind] = glm::vec4(r1a/2*cos((i+1)*M_PI/180),r1b/2*sin((i+1)*M_PI/180),0.0,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos(i*M_PI/180),r2b/2*sin(i*M_PI/180),height,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;
    vpos[ind] = glm::vec4(r2a/2*cos((i+1)*M_PI/180),r2b/2*sin((i+1)*M_PI/180),height,1.0);
    npos[ind] = glm::vec4(0.0,0.0,1.0,1.0);
    ind++;   
  }

}


int get_cone_size(float height,float r1){
  int lats = 180;
  int longts = 360;
  return lats*longts*6;
}




void cone(float height,float r1,glm::vec4 vpos[],glm::vec4 npos[]){
  float lats = 180;
  float sc = height/lats;
  int longts = 360;

  int ind = 0;


  for(int j=0;j<lats;j++){
    for(int i=0;i<longts;i++){
      float rr1 = r1 - j*(r1*1.0)/lats;
      float rr2 = r1 - (j+1)*(r1*1.0)/lats;
    vpos[ind] = glm::vec4(rr1*cos(i*M_PI/180),rr1*sin(i*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;

    vpos[ind] = glm::vec4(rr2*cos(i*M_PI/180),rr2*sin(i*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr1*cos((i+1)*M_PI/180),rr1*sin((i+1)*M_PI/180),j*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;
    vpos[ind] = glm::vec4(rr2*cos((i+1)*M_PI/180),rr2*sin((i+1)*M_PI/180),(j+1)*sc,1.0);
    npos[ind] = vpos[ind];
    ind++;

    }
  }


}

void same_colors(float a,float b, float c,int n,glm::vec4 vcol[]){
  for(int i=0;i<n;i++){
    vcol[i]=  glm::vec4(a,b,c,1.0);
  }
}
//-----------------------------------------------------------------------------------


// Frame start 

// std::string itos(int k) {
//   return std::to_string(k) + " ";
// }

// std::string itos(double k) {
//   return std::to_string(k) + " ";
// }

// std::string itos(bool k) {
//   return std::to_string(k) + " ";
// }

// double stodb(std::string s) {
//   return std::stod(s);
// }

// void saveFrame() {
//   std::ofstream frame_records;
//   frame_records.open("keyframes.txt", std::ios::app);
//   frame_records << itos(lighton1) + itos(lighton2);

//   for(auto k: humanoid) {
//     frame_records << itos(k->tx) + itos(k->ty) + itos(k->tz) + itos(k->rx) + itos(k->ry) + itos(k->rz);
//   }

//   for(auto k: dog) {
//     frame_records << itos(k->tx) + itos(k->ty) + itos(k->tz) + itos(k->rx) + itos(k->ry) + itos(k->rz);
//   }

//   frame_records << "\n";

//   frame_records.close();
// }


// void applyFrame(int kf_num) {
//   std::vector<double> frame = allframes[kf_num];
//   int j = 0;
//   lighton1 = frame[j++] > 0.5 ? 1 : 0;
//   lighton2 = frame[j++] > 0.5 ? 1 : 0;

//   for(auto k: humanoid) {
//     k->tx = frame[j++];
//     k->ty = frame[j++];
//     k->tz = frame[j++];
//     k->rx = frame[j++];
//     k->ry = frame[j++];
//     k->rz = frame[j++];
//     k->update_matrices();
//   }

//   for(auto k: dog) {
//     k->tx = frame[j++];
//     k->ty = frame[j++];
//     k->tz = frame[j++];
//     k->rx = frame[j++];
//     k->ry = frame[j++];
//     k->rz = frame[j++];
//     k->update_matrices();
//   }

// }

// std::vector<std::vector<double> > interpolate_two_frames(int t){
//   std::vector<std::vector<double> > i_frames;

//   for(int k = 0; k < 3; k++) {
//     for(int i=0;i<24;i++){
//       std::vector<double> frame;
//       for(int j=0;j<keyframes[t].size() - 6;j++){
//         frame.push_back((keyframes[t+k][j]*(24-i)+keyframes[t+k+1][j]*i)/24);
//       }
//       for(int j = keyframes[t].size() - 6; j < keyframes[t].size(); j++) {

//         double t1 = ((72-(i + k*24))/72.0);
//         double t2 = (i+k*24)/72.0;
//         if(keyframes[t][j] == keyframes[t+1][j] && keyframes[t+1][j] == keyframes[t+2][j] && keyframes[t+2][j] == keyframes[t+3][j])
//           frame.push_back(keyframes[t][j]);
//         else
//         frame.push_back(keyframes[t][j]*t1*t1*t1 + keyframes[t+1][j]*3*t1*t1*t2 + keyframes[t+2][j]*3*t1*t2*t2 + keyframes[t+3][j]*t2*t2*t2);
//       }
//       i_frames.push_back(frame);
//       frame.clear();
//     }
//   }

//   return i_frames;
// }

// void interpolate_all_frames(){
//   for(int i=0;i<keyframes.size()-3;i+=3){
//     std::vector<std::vector<double> > frames = interpolate_two_frames(i);
//     allframes.insert(allframes.end(),frames.begin(),frames.end());
//   }
//   allframes.push_back(keyframes[keyframes.size()-1]);
// }

// std::vector<double> parse_frame(std::string s) {
//   std::vector<double> frame;
//   std::istringstream is(s);
//   std::string part;
//   while(getline(is, part, ' ')) {
//     frame.push_back(stodb(part));
//   }
//   return frame;
// }

// void read_keyframes() {
//   std::string frame;
//   std::ifstream frame_records("keyframes.txt");
//   if(frame_records.is_open()) {
//     while(getline(frame_records, frame)) {
//       keyframes.push_back(parse_frame(frame));
//     }
//     frame_records.close();
//     interpolate_all_frames();
//   }
//   else {
//     playback = 0;
//     std::cout << "Unable to open keyframes.txt file";
//   }
// }

// void capture_frame(unsigned int framenum)
// {
//   //global pointer float *pRGB
//   pRGB = new unsigned char [3 * (1024+1) * (1024 + 1) ];


//   // set the framebuffer to read
//   //default for double buffered
//   glReadBuffer(GL_BACK);

//   glPixelStoref(GL_PACK_ALIGNMENT,1);//for word allignment

//   glReadPixels(0, 0, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, pRGB);
//   char filename[200];
//   sprintf(filename,"frame_%04d.ppm",framenum);
//   std::ofstream out(filename, std::ios::out);
//   out<<"P6"<<std::endl;
//   out<<1024<<" "<<1024<<" 255"<<std::endl;
//   out.write(reinterpret_cast<char const *>(pRGB), (3 * (1024+1) * (1024 + 1)) * sizeof(int));
//   out.close();

//   //function to store pRGB in a file named count
//   delete pRGB;
// }


// Frame end

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("07_vshader.glsl");
  std::string fragment_shader_file("07_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vTexture = glGetAttribLocation( shaderProgram, "vTexture" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  GLuint tex=LoadTexture("./images/wall.bmp",512,512);
  GLuint tabletoptexture=LoadTexture("./images/frame.bmp",256,256);
  GLuint lamptoptexture=LoadTexture("./images/lamp.bmp",256,256);
  GLuint stooltoptexture=LoadTexture("./images/stool.bmp",256,256);
  GLuint chairbasetexture=LoadTexture("./images/stool.bmp",256,256);
  GLuint chairbacktexture=LoadTexture("./images/stool.bmp",256,256);
  GLuint frametexture=LoadTexture("./images/frame.bmp",256,256);
  GLuint cupboardtexture=LoadTexture("./images/cupboard.bmp",256,256);
  
  // GLuint tex=LoadTexture("images/stones.bmp",512,512);
	// glBindTexture(GL_TEXTURE_2D, tex);

  // Creating the hierarchy:
  colorbox();
  room();

  for(int i=0;i<174;i++) roomnormal[i] = roompos[i];
  roombox = new csX75::HNode(NULL,174,roompos,roomcol,roomnormal,tex_coords,sizeof(roompos),sizeof(roomcol), sizeof(roomnormal),sizeof(tex_coords),true,tex);

//-----------------------------------------------furniture---------------------------------------------------

  //---------------------table-------------------------------

  float tabletoplength = 200;
  float tabletopwidth = 100;
  float tabletopthickness = 10;
  float tablelegslength = 100;
  float tablelegsthickness = 5;

  tabletoptexfill();

  cuboid(tabletoplength,tabletopwidth,tabletopthickness,tabletoppos,tabletopnormal);
  same_colors(0.5,0.2,0.1,36,tabletopcol);
  tabletop = new csX75::HNode(roombox,36,tabletoppos,tabletopcol,tabletopnormal,tabletoptex,sizeof(tabletoppos),sizeof(tabletopcol),sizeof(tabletopnormal),sizeof(tabletoptex),true,tabletoptexture);
  tabletop->change_parameters(roomlength/2,tablelegslength,roomdepth/2,-90,180,0);

  cuboid(tablelegsthickness,tablelegsthickness,tablelegslength,tableleg1pos,tableleg1normal);
  same_colors(0.7,0.4,0.3,36,tableleg1col);
  tableleg1 = new csX75::HNode(tabletop,36,tableleg1pos,tableleg1col,tableleg1normal,NULL,sizeof(tableleg1pos),sizeof(tableleg1col),sizeof(tableleg1normal),0,false,0);
  tableleg1->change_parameters((tabletoplength-tablelegsthickness)/2.0,(tabletopwidth-tablelegsthickness)/2.0,(tablelegslength+tabletopthickness)/2.0,0,0,0);

  cuboid(tablelegsthickness,tablelegsthickness,tablelegslength,tableleg2pos,tableleg2normal);
  same_colors(0.7,0.4,0.3,36,tableleg2col);
  tableleg2 = new csX75::HNode(tabletop,36,tableleg2pos,tableleg2col,tableleg2normal,NULL,sizeof(tableleg2pos),sizeof(tableleg2col),sizeof(tableleg2normal),0,false,0);
  tableleg2->change_parameters((tabletoplength-tablelegsthickness)/2.0,-1*(tabletopwidth-tablelegsthickness)/2.0,(tablelegslength+tabletopthickness)/2.0,0,0,0);

  cuboid(tablelegsthickness,tablelegsthickness,tablelegslength,tableleg3pos,tableleg3normal);
  same_colors(0.7,0.4,0.3,36,tableleg3col);
  tableleg3 = new csX75::HNode(tabletop,36,tableleg3pos,tableleg3col,tableleg3normal,NULL,sizeof(tableleg3pos),sizeof(tableleg3col),sizeof(tableleg3normal),0,false,0);
  tableleg3->change_parameters(-1*(tabletoplength-tablelegsthickness)/2.0,(tabletopwidth-tablelegsthickness)/2.0,(tablelegslength+tabletopthickness)/2.0,0,0,0);

  cuboid(tablelegsthickness,tablelegsthickness,tablelegslength,tableleg4pos,tableleg4normal);
  same_colors(0.7,0.4,0.3,36,tableleg4col);
  tableleg4 = new csX75::HNode(tabletop,36,tableleg4pos,tableleg4col,tableleg4normal,NULL,sizeof(tableleg4pos),sizeof(tableleg4col),sizeof(tableleg4normal),0,false,0);
  tableleg4->change_parameters(-1*(tabletoplength-tablelegsthickness)/2.0,-1*(tabletopwidth-tablelegsthickness)/2.0,(tablelegslength+tabletopthickness)/2.0,0,0,0);


  //---------------------------lamp-------------------------------------

  float lampbasediameter = 10;
  float lampbasethickness = 5;
  float lamptrunklength = 25;
  float lamptrunkthickness = 5;
  float lamptopdiameter1 = 20;
  float lamptopdiameter2 = 6;
  float lamptopheight = 30;

  lamptoptexfill();

  int lampbasesize = get_frustom_size(lampbasethickness,lampbasediameter,lampbasediameter);
  frustom(lampbasethickness,lampbasediameter,lampbasediameter,lampbasepos,lampbasenormal);
  same_colors(0.3,0.3,0.5,lampbasesize,lampbasecol);
  lampbase = new csX75::HNode(tabletop,lampbasesize,lampbasepos,lampbasecol,lampbasenormal,NULL,sizeof(lampbasepos),sizeof(lampbasecol),sizeof(lampbasenormal),0,false,0);
  lampbase->change_parameters(-tabletoplength*2/3,tabletopwidth/2,0,180,0,0);

  int lamptrunksize = get_frustom_size(lamptrunklength,lamptrunkthickness,lamptrunkthickness);
  frustom(lamptrunklength,lamptrunkthickness,lamptrunkthickness,lamptrunkpos,lamptrunknormal);
  same_colors(0.5,0.6,0.6,lamptrunksize,lamptrunkcol);
  lamptrunk = new csX75::HNode(lampbase,lamptrunksize,lamptrunkpos,lamptrunkcol,lamptrunknormal,NULL,sizeof(lamptrunkpos),sizeof(lamptrunkcol),sizeof(lamptrunknormal),0,false,0);

  int lamptopsize = get_frustom_size(lamptopheight,lamptopdiameter1,lamptopdiameter2);
  frustom(lamptopheight,lamptopdiameter1,lamptopdiameter2,lamptoppos,lamptopnormal);
  same_colors(1,0.5,0.1,lamptopsize,lamptopcol);
  lamptop = new csX75::HNode(lamptrunk,lamptopsize,lamptoppos,lamptopcol,lamptopnormal,lamptoptex,sizeof(lamptoppos),sizeof(lamptopcol),sizeof(lamptopnormal),sizeof(lamptoptex),true,lamptoptexture);
  lamptop->change_parameters(0,0,lamptrunklength,0,0,0);


//   //-------------------stool------------------------------------

  float stooltopthickness = 10;
  float stooltopdiameter = 40;
  float stoollegthickness = 5;
  float stoollegheight = 60;

  stooltoptexfill();

  int stooltopsize = get_frustom_size(stooltopthickness,stooltopdiameter,stooltopdiameter);
  frustom(stooltopthickness,stooltopdiameter,stooltopdiameter,stooltoppos,stooltopnormal);
  same_colors(0.1,0.2,0.1,stooltopsize,stooltopcol);
  stooltop = new csX75::HNode(roombox,stooltopsize,stooltoppos,stooltopcol,stooltopnormal,stooltoptex,sizeof(stooltoppos),sizeof(stooltopcol),sizeof(stooltopnormal),sizeof(stooltoptex),true,stooltoptexture);
  stooltop->change_parameters(roomlength/3,stoollegheight,4*roomdepth/5,90,0,0);

  int stoolleg1size = get_frustom_size(stoollegheight,stoollegthickness,stoollegthickness);
  frustom(stoollegheight,stoollegthickness,stoollegthickness,stoolleg1pos,stoolleg1normal);
  same_colors(0.3,0.3,0.5,stoolleg1size,stoolleg1col);
  stoolleg1 = new csX75::HNode(stooltop,stoolleg1size,stoolleg1pos,stoolleg1col,stoolleg1normal,NULL,sizeof(stoolleg1pos),sizeof(stoolleg1col),sizeof(stoolleg1normal),0,false,0);
  stoolleg1->change_parameters(stooltopdiameter*0.7/1.414,stooltopdiameter*0.7/1.414,stooltopthickness,0,0,0);

  int stoolleg2size = get_frustom_size(stoollegheight,stoollegthickness,stoollegthickness);
  frustom(stoollegheight,stoollegthickness,stoollegthickness,stoolleg2pos,stoolleg2normal);
  same_colors(0.3,0.3,0.5,stoolleg2size,stoolleg2col);
  stoolleg2 = new csX75::HNode(stooltop,stoolleg2size,stoolleg2pos,stoolleg2col,stoolleg2normal,NULL,sizeof(stoolleg2pos),sizeof(stoolleg2col),sizeof(stoolleg2normal),0,false,0);
  stoolleg2->change_parameters(stooltopdiameter*0.7/1.414,-1*stooltopdiameter*0.7/1.414,stooltopthickness,0,0,0);

  int stoolleg3size = get_frustom_size(stoollegheight,stoollegthickness,stoollegthickness);
  frustom(stoollegheight,stoollegthickness,stoollegthickness,stoolleg3pos,stoolleg3normal);
  same_colors(0.3,0.3,0.5,stoolleg3size,stoolleg3col);
  stoolleg3 = new csX75::HNode(stooltop,stoolleg3size,stoolleg3pos,stoolleg3col,stoolleg3normal,NULL,sizeof(stoolleg3pos),sizeof(stoolleg3col),sizeof(stoolleg3normal),0,false,0);
  stoolleg3->change_parameters(-1*stooltopdiameter*0.7/1.414,stooltopdiameter*0.7/1.414,stooltopthickness,0,0,0);

  int stoolleg4size = get_frustom_size(stoollegheight,stoollegthickness,stoollegthickness);
  frustom(stoollegheight,stoollegthickness,stoollegthickness,stoolleg4pos,stoolleg4normal);
  same_colors(0.3,0.3,0.5,stoolleg4size,stoolleg4col);
  stoolleg4 = new csX75::HNode(stooltop,stoolleg4size,stoolleg4pos,stoolleg4col,stoolleg4normal,NULL,sizeof(stoolleg4pos),sizeof(stoolleg4col),sizeof(stoolleg4normal),0,false,0);
  stoolleg4->change_parameters(-1*stooltopdiameter*0.7/1.414,-1*stooltopdiameter*0.7/1.414,stooltopthickness,0,0,0);


//   //--------------------cupboard--------------------------
  float cupboardlength = 150;
  float cupboardwidth = 100;
  float cupboardheight = 400;

  cupboardtexfill();

  cuboid(cupboardlength,cupboardwidth,cupboardheight,cupboardpos,cupboardnormal);
  same_colors(0.5,0.2,0.1,36,cupboardcol);
  cupboard = new csX75::HNode(roombox,36,cupboardpos,cupboardcol,cupboardnormal,cupboardtex,sizeof(cupboardpos),sizeof(cupboardcol),sizeof(cupboardnormal),sizeof(cupboardtex),true,cupboardtexture);
  cupboard->change_parameters(roomlength/2,cupboardheight/2,roomdepth-cupboardwidth,90,0,0);

//   //-------------------chair----------------------------------

  float chairbaselength = 50;
  float chairbasewidth = 60;
  float chairbasethickness = 5;
  float chairlegslength = 50;
  float chairlegsthickness = 5;
  float chairbacklength = 60;
  float chairbackwidth = 50;
  float chairbackthickness = 5; 

  chairbasetexfill();

  chairbacktexfill();

  cuboid(chairbaselength,chairbasewidth,chairbasethickness,chairbasepos,chairbasenormal);
  same_colors(0.5,0.1,0.1,36,chairbasecol);
  chairbase = new csX75::HNode(roombox,36,chairbasepos,chairbasecol,chairbasenormal,chairbasetex,sizeof(chairbasepos),sizeof(chairbasecol),sizeof(chairbasenormal),sizeof(chairbasetex),true,chairbasetexture);
  chairbase->change_parameters(2*roomlength/3,chairlegslength,roomdepth-chairbaselength,90,0,-90);

  cuboid(chairbacklength,chairbackwidth,chairbackthickness,chairbackpos,chairbacknormal);
  same_colors(0.2,0.1,0.1,36,chairbackcol);
  chairback = new csX75::HNode(chairbase,36,chairbackpos,chairbackcol,chairbacknormal,chairbacktex,sizeof(chairbackpos),sizeof(chairbackcol),sizeof(chairbacknormal),sizeof(chairbacktex),true,chairbacktexture);
  chairback->change_parameters(0,(chairbasewidth-chairbackthickness)/2.0,-1*(chairbacklength+2*chairbasethickness)/2.0,90,0,0);

  cuboid(chairlegsthickness,chairlegsthickness,chairlegslength,chairleg1pos,chairleg1normal);
  same_colors(0.7,0.4,0.3,36,chairleg1col);
  chairleg1 = new csX75::HNode(chairbase,36,chairleg1pos,chairleg1col,chairleg1normal,NULL,sizeof(chairleg1pos),sizeof(chairleg1col),sizeof(chairleg1normal),0,false,0);
  chairleg1->change_parameters((chairbaselength-chairlegsthickness)/2.0,(chairbasewidth-chairlegsthickness)/2.0,(chairlegslength+chairbasethickness)/2.0,0,0,0);

  cuboid(chairlegsthickness,chairlegsthickness,chairlegslength,chairleg2pos,chairleg2normal);
  same_colors(0.7,0.4,0.3,36,chairleg2col);
  chairleg2 = new csX75::HNode(chairbase,36,chairleg2pos,chairleg2col,chairleg2normal,NULL,sizeof(chairleg2pos),sizeof(chairleg2col),sizeof(chairleg2normal),0,false,0);
  chairleg2->change_parameters((chairbaselength-chairlegsthickness)/2.0,-1*(chairbasewidth-chairlegsthickness)/2.0,(chairlegslength+chairbasethickness)/2.0,0,0,0);

  cuboid(chairlegsthickness,chairlegsthickness,chairlegslength,chairleg3pos,chairleg3normal);
  same_colors(0.7,0.4,0.3,36,chairleg3col);
  chairleg3 = new csX75::HNode(chairbase,36,chairleg3pos,chairleg3col,chairleg3normal,NULL,sizeof(chairleg3pos),sizeof(chairleg3col),sizeof(chairleg3normal),0,false,0);
  chairleg3->change_parameters(-1*(chairbaselength-chairlegsthickness)/2.0,(chairbasewidth-chairlegsthickness)/2.0,(chairlegslength+chairbasethickness)/2.0,0,0,0);

  cuboid(chairlegsthickness,chairlegsthickness,chairlegslength,chairleg4pos,chairleg4normal);
  same_colors(0.7,0.4,0.3,36,chairleg4col);
  chairleg4 = new csX75::HNode(chairbase,36,chairleg4pos,chairleg4col,chairleg4normal,NULL,sizeof(chairleg4pos),sizeof(chairleg4col),sizeof(chairleg4normal),0,false,0);
  chairleg4->change_parameters(-1*(chairbaselength-chairlegsthickness)/2.0,-1*(chairbasewidth-chairlegsthickness)/2.0,(chairlegslength+chairbasethickness)/2.0,0,0,0);


//   //-----------------frame-------------

  float framelength = 100;
  float framewidth = 10;
  float frameheight = 100;

  frametexfill();

  cuboid(framelength,framewidth,frameheight,framepos,framenormal);
  same_colors(0.5,0.2,0.1,36,framecol);
  frame = new csX75::HNode(roombox,36,framepos,framecol,framenormal,frametex,sizeof(framepos),sizeof(framecol),sizeof(framenormal),sizeof(frametex),true,frametexture);
  frame->change_parameters(roomlength*4.0/5.0-framewidth,roomheight*2.0/3.0,roomdepth-wallthickness-framewidth,90,0,0);

  //-----------------------------------------------------------------------------------------------------------



  lowerbox = new csX75::HNode(tabletop,num_vertices_box,v_positions_box,v_colors_box,v_normals_box,NULL, sizeof(v_positions_box),sizeof(v_colors_box),sizeof(v_normals_box),0,false,0);
  lowerbox->change_parameters(-tabletoplength/5,tabletopwidth/3,-2*height,180.0,0.0,0.0);
  upperbox = new csX75::HNode(lowerbox,num_vertices_box,v_positions_box,v_colors_box,v_normals_box,NULL,sizeof(v_positions_box),sizeof(v_colors_box),sizeof(v_normals_box),0,false,0);
  upperbox->change_parameters(0.0,width,0.0,120.0,0.0,0.0);




  //------------------------------------------------- Humanoid---------------------------------------------------------


  int torso3size = get_elliptical_frustom_size(5,6,3,7,3);
  elliptical_frustom(5,6,3,7,3,torso3pos,torso3normal);
  same_colors(1.0, 0.0, 0.0,torso3size,torso3col);
  torso3 = new csX75::HNode(lowerbox,torso3size,torso3pos,torso3col,torso3normal,NULL,sizeof(torso3pos),sizeof(torso3col),sizeof(torso3normal),0,false,0);
  torso3->change_parameters(length/2,width/2,18,180.0,0.0,0.0);
  humanoid.push_back(torso3);

  int torso2size = get_ellipse_size(3,6,3);
  ellipse(3,6,3,torso2pos,torso2normal);
  same_colors(0.7, 0.0, 0.0,torso2size,torso2col);
  torso2 = new csX75::HNode(torso3,torso2size,torso2pos,torso2col,torso2normal,NULL,sizeof(torso2pos),sizeof(torso2col),sizeof(torso2normal),0,false,0);
  torso2->change_parameters(0.0,0.0,0.5,180.0,0.0,0.0);
  humanoid.push_back(torso2);

  int torso1size = get_elliptical_frustom_size(7,6,3,9,4);
  elliptical_frustom(7,6,3,9,4,torso1pos,torso1normal);
  same_colors(0.9, 0.0, 0.0,torso1size,torso1col);
  torso1 = new csX75::HNode(torso2,torso1size,torso1pos,torso1col,torso1normal,NULL,sizeof(torso1pos),sizeof(torso1col),sizeof(torso1normal),0,false,0);
  torso1->change_parameters(0.0,0.0,2.5,0.0,0.0,0.0);
  humanoid.push_back(torso1);

  int shoulderlsize = get_ellipse_size(2,2,2);
  ellipse(2,2,2,shoulderlpos,shoulderlnormal);
  same_colors(0.0,0.0,0.8,shoulderlsize,shoulderlcol);
  shoulderl = new csX75::HNode(torso1,shoulderlsize,shoulderlpos,shoulderlcol,shoulderlnormal,NULL,sizeof(shoulderlpos),sizeof(shoulderlcol),sizeof(shoulderlnormal),0,false,0);
  shoulderl->change_parameters(5.5,0.0,5.5,0.0,0.0,0.0);
  humanoid.push_back(shoulderl);

  int shoulderrsize = get_ellipse_size(2,2,2);
  ellipse(2,2,2,shoulderrpos,shoulderrnormal);
  same_colors(0.0,0.0,0.8,shoulderrsize,shoulderrcol);
  shoulderr = new csX75::HNode(torso1,shoulderrsize,shoulderrpos,shoulderrcol,shoulderrnormal,NULL,sizeof(shoulderrpos),sizeof(shoulderrcol),sizeof(shoulderrnormal),0,false,0);
  shoulderr->change_parameters(-5.5,0.0,5.5,0.0,0.0,0.0);
  humanoid.push_back(shoulderr);

  int uarmlsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,uarmlpos,uarmlnormal);
  same_colors(0.8,0.0,0.0,uarmlsize,uarmlcol);
  uarml = new csX75::HNode(shoulderl,uarmlsize,uarmlpos,uarmlcol,uarmlnormal,NULL,sizeof(uarmlpos),sizeof(uarmlcol),sizeof(uarmlnormal),0,false,0);
  uarml->change_parameters(0.0,0.0,0.0,180.0,0.0,0.0);
  humanoid.push_back(uarml);

  int uarmrsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,uarmrpos,uarmrnormal);
  same_colors(0.8,0.0,0.0,uarmrsize,uarmrcol);
  uarmr = new csX75::HNode(shoulderr,uarmrsize,uarmrpos,uarmrcol,uarmrnormal,NULL,sizeof(uarmrpos),sizeof(uarmrcol),sizeof(uarmrnormal),0,false,0);
  uarmr->change_parameters(0.0,0.0,0.0,180.0,0.0,0.0);
  humanoid.push_back(uarmr);

  int elbowlsize = get_ellipse_size(1.0,1.5,1.5);
  ellipse(1.0,1.5,1.5,elbowlpos,elbowlnormal);
  same_colors(0.0,0.0,0.8,elbowlsize,elbowlcol);
  elbowl = new csX75::HNode(uarml,elbowlsize,elbowlpos,elbowlcol,elbowlnormal,NULL,sizeof(elbowlpos),sizeof(elbowlcol),sizeof(elbowlnormal),0,false,0);
  elbowl->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);
  humanoid.push_back(elbowl);

  int elbowrsize = get_ellipse_size(1.0,1.5,1.5);
  ellipse(1.0,1.5,1.5,elbowrpos,elbowrnormal);
  same_colors(0.0,0.0,0.8,elbowrsize,elbowrcol);
  elbowr = new csX75::HNode(uarmr,elbowrsize,elbowrpos,elbowrcol,elbowrnormal,NULL,sizeof(elbowrpos),sizeof(elbowrcol),sizeof(elbowrnormal),0,false,0);
  elbowr->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);
  humanoid.push_back(elbowr);

  int larmlsize = get_frustom_size(6,0.8,0.5);
  frustom(6,0.8,0.5,larmlpos,larmlnormal);
  same_colors(1.0,1.0,0.0,larmlsize,larmlcol);
  larml = new csX75::HNode(elbowl,larmlsize,larmlpos,larmlcol,larmlnormal,NULL,sizeof(larmlpos),sizeof(larmlcol),sizeof(larmlnormal),0,false,0);
  larml->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
  humanoid.push_back(larml);

  int larmrsize = get_frustom_size(6,0.8,0.5);
  frustom(6,0.8,0.5,larmrpos,larmrnormal);
  same_colors(1.0,1.0,0.0,larmrsize,larmrcol);
  larmr = new csX75::HNode(elbowr,larmrsize,larmrpos,larmrcol,larmrnormal,NULL,sizeof(larmrpos),sizeof(larmrcol),sizeof(larmrnormal),0,false,0);
  larmr->change_parameters(0.0,0.0,1.0,0.0,0.0,0.0);
  humanoid.push_back(larmr);

  int handlsize = get_ellipse_size(4,2,1.5);
  ellipse(4,2,1.5,handlpos,handlnormal);
  same_colors(1.0,0.8,0.6,handlsize,handlcol);
  handl = new csX75::HNode(larml,handlsize,handlpos,handlcol,handlnormal,NULL,sizeof(handlpos),sizeof(handlcol),sizeof(handlnormal),0,false,0);
  handl->change_parameters(0.0,0.0,5.0,0.0,0.0,0.0);
  humanoid.push_back(handr);

  int handrsize = get_ellipse_size(4,2,1.5);
  ellipse(4,2,1.5,handrpos,handrnormal);
  same_colors(1.0,0.8,0.6,handrsize,handrcol);
  handr = new csX75::HNode(larmr,handrsize,handrpos,handrcol,handrnormal,NULL,sizeof(handrpos),sizeof(handrcol),sizeof(handrnormal),0,false,0);
  handr->change_parameters(0.0,0.0,5.0,0.0,0.0,0.0);
  humanoid.push_back(handr);


  int necksize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,neckpos,necknormal);
  same_colors(0.9,0.7,0.5,necksize,neckcol);
  neck = new csX75::HNode(torso1,necksize,neckpos,neckcol,necknormal,NULL,sizeof(neckpos),sizeof(neckcol),sizeof(necknormal),0,false,0);
  neck->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);
  humanoid.push_back(neck);

  int headsize = get_ellipse_size(7,4,4);
  ellipse(7,4,4,headpos,headnormal);
  same_colors(1.0,0.8,0.6,headsize,headcol);
  head = new csX75::HNode(neck,headsize,headpos,headcol,headnormal,NULL,sizeof(headpos),sizeof(headcol),sizeof(headnormal),0,false,0);
  head->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);
  humanoid.push_back(head);

  int hiplsize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,hiplpos,hiplnormal);
  same_colors(0.0, 0.0, 0.8,hiplsize,hiplcol);
  hipl = new csX75::HNode(torso3,hiplsize,hiplpos,hiplcol,hiplnormal,NULL,sizeof(hiplpos),sizeof(hiplcol),sizeof(hiplnormal),0,false,0);
  hipl->change_parameters(2.0,0.0,5.0,0.0,0.0,0.0);
  humanoid.push_back(hipl);

  int hiprsize = get_ellipse_size(1.5,3.5,3.5);
  ellipse(1.5,3.5,3.5,hiprpos,hiprnormal);
  same_colors(0.0, 0.0, 0.8,hiprsize,hiprcol);
  hipr = new csX75::HNode(torso3,hiprsize,hiprpos,hiprcol,hiprnormal,NULL,sizeof(hiprpos),sizeof(hiprcol),sizeof(hiprnormal),0,false,0);
  hipr->change_parameters(-2.0,0.0,5.0,0.0,0.0,0.0);
  humanoid.push_back(hipr);

  int thighlsize = get_frustom_size(7,1.5,1.0);
  frustom(7,1.5,1.0,thighlpos,thighlnormal);
  same_colors(0.0, 0.0, 0.8,thighlsize,thighlcol);
  thighl = new csX75::HNode(hipl,thighlsize,thighlpos,thighlcol,thighlnormal,NULL,sizeof(thighlpos),sizeof(thighlcol),sizeof(thighlnormal),0,false,0);
  thighl->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);
  humanoid.push_back(thighl);

  int thighrsize = get_frustom_size(7,1.5,1.0);
  frustom(7,1.5,1.0,thighrpos,thighrnormal);
  same_colors(0.0, 0.0, 0.8,thighrsize,thighrcol);
  thighr = new csX75::HNode(hipr,thighrsize,thighrpos,thighrcol,thighrnormal,NULL,sizeof(thighrpos),sizeof(thighrcol),sizeof(thighrnormal),0,false,0);
  thighr->change_parameters(0.0,0.0,1.5,0.0,0.0,0.0);
  humanoid.push_back(thighr);

int kneelsize = get_ellipse_size(1.5,2.5,2.5);
  ellipse(1.5,2.5,2.5,kneelpos,kneelnormal);
  same_colors(0.0, 0.0, 0.6,kneelsize,kneelcol);
  kneel = new csX75::HNode(thighl,kneelsize,kneelpos,kneelcol,kneelnormal,NULL,sizeof(kneelpos),sizeof(kneelcol),sizeof(kneelnormal),0,false,0);
  kneel->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);
  humanoid.push_back(kneel);

  int kneersize = get_ellipse_size(1.5,2.5,2.5);
  ellipse(1.5,2.5,2.5,kneerpos,kneernormal);
  same_colors(0.0, 0.0, 0.6,kneersize,kneercol);
  kneer = new csX75::HNode(thighr,kneersize,kneerpos,kneercol,kneernormal,NULL,sizeof(kneerpos),sizeof(kneercol),sizeof(kneernormal),0,false,0);
  kneer->change_parameters(0.0,0.0,6.5,0.0,0.0,0.0);
  humanoid.push_back(kneer);

  int leglsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,leglpos,leglnormal);
  same_colors(0.0, 0.0, 0.6,leglsize,leglcol);
  legl = new csX75::HNode(kneel,leglsize,leglpos,leglcol,leglnormal,NULL,sizeof(leglpos),sizeof(leglcol),sizeof(leglnormal),0,false,0);
  legl->change_parameters(0.0,0.0,1.25,0.0,0.0,0.0);
  humanoid.push_back(legl);

  int legrsize = get_frustom_size(7,1.2,0.8);
  frustom(7,1.2,0.8,legrpos,legrnormal);
  same_colors(0.0, 0.0, 0.6,legrsize,legrcol);
  legr = new csX75::HNode(kneer,legrsize,legrpos,legrcol,legrnormal,NULL,sizeof(legrpos),sizeof(legrcol),sizeof(legrnormal),0,false,0);
  legr->change_parameters(0.0,0.0,1.25,0.0,0.0,0.0);
  humanoid.push_back(legr);


  int footlsize = get_ellipse_size(1.5,3,6);
  ellipse(1.50,3,6.0,footlpos,footlnormal);
  same_colors(0.2,0.2,0.2,footlsize,footlcol);
  footl = new csX75::HNode(legl,footlsize,footlpos,footlcol,footlnormal,NULL,sizeof(footlpos),sizeof(footlcol),sizeof(footlnormal),0,false,0);
  footl->change_parameters(0.0,1.0,7.0,0.0,0.0,0.0);
  humanoid.push_back(footl);

  int footrsize = get_ellipse_size(1.5,3,6);
  ellipse(1.5,3,6,footrpos,footrnormal);
  same_colors(0.2,0.2,0.2,footrsize,footrcol);
  footr = new csX75::HNode(legr,footrsize,footrpos,footrcol,footrnormal,NULL,sizeof(footrpos),sizeof(footrcol),sizeof(footrnormal),0,false,0);
  footr->change_parameters(0.0,1.0,7.0,0.0,0.0,0.0);
  humanoid.push_back(footr);


//   // --------------------------------------------- props ------------------------------------------------------------


  int hatsize = get_frustom_size(2,1.5,4);
  frustom(2,1.5,4,hatpos,hatnormal);
  same_colors(0.5, 0.5, 1.0,hatsize,hatcol);
  hat = new csX75::HNode(head,hatsize,hatpos,hatcol,hatnormal,NULL,sizeof(hatpos),sizeof(hatcol),sizeof(hatnormal),0,false,0);
  hat->change_parameters(0.0,0.0,6.0,0.0,0.0,0.0);


  int umbrellasticksize = get_frustom_size(15,0.3,0.3);
  frustom(15,0.3,0.3,umbrellastickpos,umbrellasticknormal);
  same_colors(0.5, 0.5, 1.0,umbrellasticksize,umbrellastickcol);
  umbrellastick = new csX75::HNode(handr,umbrellasticksize,umbrellastickpos,umbrellastickcol,umbrellasticknormal,NULL,sizeof(umbrellastickpos),sizeof(umbrellastickcol),sizeof(umbrellasticknormal),0,false,0);
  umbrellastick->change_parameters(0.0,0.0,4.0,0.0,0.0,0.0);

  int umbrellafoldedsize = get_frustom_size(12,0.9,0.4);
  frustom(12,0.9,0.4,umbrellafoldedpos,umbrellafoldednormal);
  same_colors(1.0, 0.0, 0.0,umbrellafoldedsize,umbrellafoldedcol);
  umbrellafolded = new csX75::HNode(umbrellastick,umbrellafoldedsize,umbrellafoldedpos,umbrellafoldedcol,umbrellafoldednormal,NULL,sizeof(umbrellafoldedpos),sizeof(umbrellafoldedcol),sizeof(umbrellafoldednormal),0,false,0);
  umbrellafolded->change_parameters(0.0,0.0,3.0,0.0,0.0,0.0);


  int umbrellaopensize = get_cone_size(5,9);
  cone(5,9,umbrellaopenpos,umbrellaopennormal);
  same_colors(1.0, 0.0, 0.0,umbrellaopensize,umbrellaopencol);
  umbrellaopen = new csX75::HNode(umbrellastick,umbrellaopensize,umbrellaopenpos,umbrellaopencol,umbrellaopennormal,NULL,sizeof(umbrellaopenpos),sizeof(umbrellaopencol),sizeof(umbrellaopennormal),0,false,0);
  umbrellaopen->change_parameters(1000.0,0.0,10.0,0.0,0.0,0.0);

  

//---------------------------------------------------- dog  -----------------------------------------------------------

  int dogtrunksize = get_ellipse_size(15,8,6);
  ellipse(15,8,6,dogtrunkpos,dogtrunknormal);
  same_colors(0.7,0.7,0.5,dogtrunksize,dogtrunkcol);
  dogtrunk = new csX75::HNode(lowerbox,dogtrunksize,dogtrunkpos,dogtrunkcol,dogtrunknormal,NULL,sizeof(dogtrunkpos),sizeof(dogtrunkcol),sizeof(dogtrunknormal),0,false,0);
  dogtrunk->change_parameters(2.0*length/3.0,width/2,height,90.0,90.0,0.0);
  dog.push_back(dogtrunk);
  
  int dognecksize = get_frustom_size(4,1.6,0.8);
  frustom(4,1.6,0.8,dogneckpos,dognecknormal);
  same_colors(0.7,0.7,0.7,dognecksize,dogneckcol);
  dogneck = new csX75::HNode(dogtrunk,dognecksize,dogneckpos,dogneckcol,dognecknormal,NULL,sizeof(dogneckpos),sizeof(dogneckcol),sizeof(dognecknormal),0,false,0);
  dogneck->change_parameters(0.0,1.6,1.6,42.0,180.0,0.0);
  dog.push_back(dogneck);

  int dogheadsize = get_ellipse_size(5,3,2);
  ellipse(5,3,2,dogheadpos,dogheadnormal);
  same_colors(0.5,0.5,0.5,dogheadsize,dogheadcol);
  doghead = new csX75::HNode(dogneck,dogheadsize,dogheadpos,dogheadcol,dogheadnormal,NULL,sizeof(dogheadpos),sizeof(dogheadcol),sizeof(dogheadnormal),0,false,0);
  doghead->change_parameters(0,-4,4,-90,0,0);
  dog.push_back(doghead);

  int dogarm1size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm1pos,dogarm1normal);
  same_colors(0.3,0.3,0.5,dogarm1size,dogarm1col);
  dogarm1 = new csX75::HNode(dogtrunk,dogarm1size,dogarm1pos,dogarm1col,dogarm1normal,NULL,sizeof(dogarm1pos),sizeof(dogarm1col),sizeof(dogarm1normal),0,false,0);
  dogarm1->change_parameters(-2,-2.5,4,90,0,0);
  dog.push_back(dogarm1);

  int dogarm2size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm2pos,dogarm2normal);
  same_colors(0.3,0.3,0.5,dogarm2size,dogarm2col);
  dogarm2 = new csX75::HNode(dogtrunk,dogarm2size,dogarm2pos,dogarm2col,dogarm2normal,NULL,sizeof(dogarm2pos),sizeof(dogarm2col),sizeof(dogarm2normal),0,false,0);
  dogarm2->change_parameters(2,-2.5,4,90,0,0);
  dog.push_back(dogarm2);

  int dogarm3size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm3pos,dogarm3normal);
  same_colors(0.3,0.3,0.5,dogarm3size,dogarm3col);
  dogarm3 = new csX75::HNode(dogtrunk,dogarm3size,dogarm3pos,dogarm3col,dogarm3normal,NULL,sizeof(dogarm3pos),sizeof(dogarm3col),sizeof(dogarm3normal),0,false,0);
  dogarm3->change_parameters(-2,-2.5,11,90,0,0);
  dog.push_back(dogarm3);

  int dogarm4size = get_frustom_size(6,1,0.5);
  frustom(6,1,0.5,dogarm4pos,dogarm4normal);
  same_colors(0.3,0.3,0.5,dogarm4size,dogarm4col);
  dogarm4 = new csX75::HNode(dogtrunk,dogarm4size,dogarm4pos,dogarm4col,dogarm4normal,NULL,sizeof(dogarm4pos),sizeof(dogarm4col),sizeof(dogarm4normal),0,false,0);
  dogarm4->change_parameters(2,-2.5,11,90,0,0);
  dog.push_back(dogarm4);

  int dogtailsize = get_frustom_size(10,0.5,0.1);
  frustom(10,0.5,0.1,dogtailpos,dogtailnormal);
  same_colors(0.3,0.3,0.3,dogtailsize,dogtailcol);
  dogtail = new csX75::HNode(dogtrunk,dogtailsize,dogtailpos,dogtailcol,dogtailnormal,NULL,sizeof(dogtailpos),sizeof(dogtailcol),sizeof(dogtailnormal),0,false,0);
  dogtail->change_parameters(0,1.5,13.5,-40,0,0);
  dog.push_back(dogtail);

  //-----------------------------------------------------------------------------------------------------------
  root_node = curr_node = roombox;

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0);
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(roomlength/2.0,200,roomdepth/2.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 7000.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-wsize*4, wsize*4, -wsize*4, 5*wsize, 4*wsize, -wsize*4);

  // glm::mat4 id = glm::mat4(1.0f);
  // glm::vec3 translation_amt(g_xtrans*trans_factor,g_ytrans*trans_factor,g_ztrans*trans_factor);
  // c_translation_matrix = glm::translate(id, translation_amt);

  // view_matrix = projection_matrix*lookat_matrix*c_rotation_matrix*c_translation_matrix;
  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);


  roombox->render_tree();
  // lowerbox->render_tree();
  // torso3->render_tree();
  // dogtrunk->render_tree();

  // tabletop->render_tree();
  roombox->render_tree();
  // cupboard->render_tree();
  lampbase->render_tree();
}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1024, 1024, "CS475/CS675 Tutorial 7: Hierarchical Modelling", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {

      // if(playback && glfwGetTime()>num_frames*timer){
      //   // std::cout<<fps<<std::endl;
      //   // std::cout<<glfwGetTime()<<std::endl;
      //   applyFrame(num_frames);
      //   // Uncomment to get frames
      //   // capture_frame(num_frames);
      //   num_frames++;
      //   if(num_frames == allframes.size())
      //       playback = 0;
      // }
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

