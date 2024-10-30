#include "utils.h" // funciones externas utiles para la libreria
#ifndef SimpleMenu_h
#define SimpleMenu_h
#define U8g2 0 
#define GFX 1

#if LIBRARY == U8g2
    #include <U8g2lib.h>
    #define LCDWidth                        disp.getDisplayWidth() 
    #define LCDHeight                       disp.getDisplayHeight()
    #define STRHeight                       disp.getMaxCharHeight()
    #define STRWidth(t)                        disp.getStrWidth(t)
    #define CENTER_H(t)                 ((LCDWidth - (STRWidth(t))) / 2)
    #define CENTER_V                 ((LCDHeight - (STRHeight)) / 2)
    #define RIGHT_H(t)                  (LCDWidth -  STRWidth(t))
#elif LIBRARY == 1
      #include <Adafruit_GFX.h>
      #define LCDWidth                        disp.width()
      #define LCDHeight                       disp.height()
      #define STRHeight(t)                    strHeight(t)
      #define STRWidth(t)                     strWidth(t)
      #define CENTER_H(t)                ((LCDWidth - STRWidth(t)) / 2)
      #define CENTER_V(t)                ((LCDHeight - STRHeight(t)) / 2)
      #define RIGHT_H(t)                  (LCDWidth -  STRWidth(t))
     //size font adafruit
      #define tx 2.4
      #define ty 1.9
      #define ix 2.1
      #define iy 1.9
#endif
enum { LEFT,CENTER,RIGHT };

class sm
{
    public:
    #if LIBRARY == U8g2
    sm(U8G2& dispPointer);
    const uint8_t *titleFont=NULL; // establece la fuente para el titulo solo disponible para U8g2
    const uint8_t *itemFont=NULL; // establece la fuente para los items solo disponible para U8g2
    #elif LIBRARY == GFX
    sm(Adafruit_GFX& dispPointer);
    #endif
    void Show(); //metodo que muestra el menu en pantalla
    void UpdateOff(); //metodo que apaga la pantalla pasado el tiempo de autoOff
    template <typename T, class tipo> 
    void Assign(T (&opt), tipo id,  bool title=true); // metodo para asignar las opciones al menu opt:opciones , id: un identificador para el menu puede ser numerico o texto, title: true si la primera opcion es titulo
    template <typename T,class tipo>  
    void Root(T (&opt), tipo id,  bool title=true); // se puede establecer un menu raiz, el cual solo se define una vez
    void Root(); //despues de estar definido se llama el metodo sin argumentos
    void Pause(bool opt); //pausa la actualizacion del menu en pantalla, util para imprimir en pantalla estando en un submenu
    template <class tipo> 
    bool Select(uint8_t sel, tipo id); // metodo que retorna verdadero si se esta seleccionando la opcion actual del menu actual
    //uint8_t Select(tipo id); // metodo que retorna verdadero si se esta seleccionando la opcion actual del menu actual
    void SetAutoOff(uint8_t timeout);  // metodo que establece un tiempo de apagado para la pantalla en segundos
    void Up(); //metodo que desplaza hacia una opcion arriba en el menu
    void Down();//metodo que desplaza hacia una opcion abajo en el menu
    void fullUp(); //metodo que desplaza al primer item en el menu
    void fullDown();//metodo que desplaza al ultimo item en el menu

    void Message(String _text,uint8_t align=LEFT,int wait=2000); //metodo que despliega un mensaje en pantalla, recibe una cadena de caracteres, una lineacion por defecto a la izquierda y un tiempo de espera en pantalla
    int8_t GetInterline(); //metodo que devuelve el valor de interlinea establecido
    bool format=true; // opcion quedefine si el texto se formatea asi, true: texto de titulos en mayusculas, texto de los items en letra capital, false: se muestran tal cual se escribieron
    uint8_t alignTitle=LEFT; // opcion que define la alineacion del titulo izquierda por defecto
    uint8_t alignItem=LEFT; // opcion que define la alineacion de los items izquierda por defecto
    int8_t interline = -1; // opcion que define el interlineado entre los items       
    int8_t max_lines = -1; // variable donde se establece el numero maximo de lineas que se puede mostrar segun la altura de la pantalla y de la fuente seleccionada
uint8_t _selected = 0; //variable que almacena la opcion seleccionada actualmente
    private:
    #if LIBRARY == U8g2
    U8G2& disp;
    #elif LIBRARY == GFX
    Adafruit_GFX& disp;
    uint16_t strWidth(String str); //funcion que devuelve el ancho en pixeles de un string solo para AdafruitGFX
    uint16_t strHeight(String str); //funcion que devuelve el alto en pixeles de un string solo para AdafruitGFX
    #endif    

    txtMenu *_opt; // opciones en formato string
    String _Id;    // variable que guarda el id del menu en formato string
    uint8_t _id ; // variable que guarda el id del menu en formato numerico
    txtMenu *_root_opt; // almacena el menu principal establecido con el metodo Root
    uint8_t _root_id=255; // identificador numerico por defecto para el menu principal
    String _root_Id;  // identificador tipo string por defecto vacio para el menu principal
    bool _title=true; //por defecto la primera linea de los menus es el titulo no una opcion seleccionable, si se pone a false, todas las lienas seran opciones seleccionables
    uint8_t _nroItems; // variable que almacena el numero de items que tiene el menu
    
    uint8_t _max_lines = 0; // variable donde se establece el numero maximo de lineas que se puede mostrar segun la altura de la pantalla y de la fuente seleccionada
    uint8_t _titleht=0; //variable que almacena la altura en pixeles del titulo
    uint8_t _lineht =0; //variable que almacena la altura en pixeles de una opcion
    int8_t _interline = 0; // opcion que define el interlineado entre los items 
    uint8_t _timeout=0; // variable requerida para la funcion SetAutoOff
    uint32_t _lastActivity = 0; // variable requerida para la funcion SetAutoOff
    uint32_t _tTime = 0; // variable requerida para la funcion SetAutoOff
    bool _change=true; //variable que define si el menu ha cambiado, decir si se selecciono alguna opcion  para actualizar el display
    bool _pause=false; //variable que define si el menu ha sido pausado
     
};
#endif

template <typename T, class tipo>  
void sm::Assign(T (&opt), tipo id,bool title)
{
byte tam=size(opt);
String test=String(id);
if(isNumeric(test)){_id=test.toInt();} else{_Id=test;}

_opt = new txtMenu[tam]; 

for (uint8_t i = 0; i < tam; i++) 
{
_opt[i]=opt[i]; 
if(format){_opt[i].toLowerCase();_opt[i][0]=toUpperCase(_opt[i][0]);}
}

_nroItems= tam-1;
_title=title;

 #if LIBRARY == U8g2
if(_title){if(format){ _opt[0].toUpperCase();}
   disp.setFont(titleFont);  
   _titleht = STRHeight;
   _selected=1;   
    }
    disp.setFont(itemFont);
    _lineht = STRHeight;
    _titleht=(_titleht==0)?_lineht:_titleht;
   _max_lines =  round(((LCDHeight*1.0)-(_titleht*1.0)) / (_lineht*1.0));
   _max_lines =((LCDHeight-_titleht)-(_lineht*_max_lines)>0)?_max_lines:_max_lines=_max_lines-2;
   //_interline=round(((LCDHeight*1.0-_titleht*1.0)-(_lineht*1.0*_max_lines*1.0))/_max_lines*1.0);
  _interline=round(  ( (LCDHeight*1.0) / ((_max_lines+_title)*1.0))  /(_max_lines+_title));
   _interline=(interline!=-1)?interline:_interline;
   _max_lines=(max_lines!=-1)?max_lines:_max_lines;

 #elif LIBRARY == GFX
 if(_title){if(format){ _opt[0].toUpperCase();}
   disp.setTextSize(tx,ty);//2.0 y 1.7
   _titleht=STRHeight(_opt[0]);
   _selected=1;   
    }
  disp.setTextSize(ix,iy); //2.0 y 1.0
   _lineht=STRHeight(_opt[0]);
   _titleht=(_titleht==0)?_lineht:_titleht;
   _max_lines =  round(((LCDHeight*1.0)-(_titleht*1.0)) / (_lineht*1.0));
   _max_lines =((LCDHeight-_titleht)-(_lineht*_max_lines)>=0)?_max_lines:_max_lines=_max_lines-2;
  // _interline=round(((LCDHeight*1.0-_titleht*1.0)-(_lineht*1.0*_max_lines*1.0))/_max_lines*1.0);
  _interline=round(  ( (LCDHeight*1.0) / ((_max_lines+_title)*1.0))  /(_max_lines+_title));
  _interline=(interline!=-1)?interline:_interline;
  _max_lines=(max_lines!=-1)?max_lines:_max_lines;

 #endif

 }
#if LIBRARY == U8g2
sm::sm(U8G2& dispPointer): disp(dispPointer)
{
if(LCDWidth*LCDHeight<=4096){ // si la resolucion de la pantalla elegida es menor a 4096 se establece una fuente pequeña
if(titleFont==NULL && itemFont==NULL){titleFont=itemFont=u8g2_font_roentgen_nbp_tr;} //sino se establece ninguna fuente esta es establecida por defecto
if(titleFont==NULL && itemFont!=NULL){titleFont=itemFont;}
if(titleFont!=NULL && itemFont==NULL){itemFont=titleFont;}
}
else 
{
if(titleFont==NULL && itemFont==NULL){titleFont=itemFont=u8g2_font_9x15B_tr;}  // si la resolucion de la pantalla elegida es mayor a 4096 se establece una fuente grande
if(titleFont==NULL && itemFont!=NULL){titleFont=itemFont;} //sino se establece ninguna fuente esta es establecida por defecto
if(titleFont!=NULL && itemFont==NULL){itemFont=titleFont;} 
}
}
void sm::UpdateOff() 
{
_tTime = (unsigned long)(millis() - _lastActivity);      // time since last activity  
if(_tTime > (_timeout * 1000) && _timeout>0) {disp.clear();}
}
//Show Menu
void sm::Show() 
{   
if(_change)
{
    disp.setFontPosTop();
    disp.clearBuffer();
    disp.setCursor(0, 0);
    uint8_t cur_x=0;
    if(_title){
          if(alignTitle==CENTER || alignTitle==RIGHT)
          {cur_x=(alignTitle==CENTER)?CENTER_H(_opt[0].c_str()):RIGHT_H(_opt[0].c_str());}
          disp.setCursor(cur_x, 0);
          disp.setFont(titleFont);  disp.print(_opt[0].c_str());
            }
    disp.setFont(itemFont);
    uint8_t initLine= (_selected<=_max_lines)? (_title)?1:0 : (_selected-_max_lines) +_title ; 
     cur_x=2;
     for (uint8_t i=initLine; i <=_nroItems ; i++) {
     uint8_t  j=(_selected>_max_lines)?(i-initLine)+_title:i;
          if(alignItem==CENTER || alignItem==RIGHT){cur_x=(alignItem==CENTER)?CENTER_H(_opt[i].c_str()):RIGHT_H(_opt[i].c_str());}
          disp.setCursor(cur_x, (_lineht*j)+_interline);       
       if (i == _selected) {
           uint8_t w = STRWidth(_opt[i].c_str()); 
           disp.drawBox(cur_x,(_lineht*j)+_interline, w+4, _lineht-2);
           disp.setDrawColor(0);
           disp.print(_opt[i].c_str());
           disp.setDrawColor(1);
       
      } else if (i != _selected) {
        disp.print(_opt[i].c_str());
      }

}
disp.sendBuffer();
_change=false;
}
UpdateOff();
}
//-------------------------------------------------------------------------------------------------------------//
#elif LIBRARY == GFX
sm::sm(Adafruit_GFX& dispPointer): disp(dispPointer)
{}
void sm::UpdateOff() 
{
_tTime = (unsigned long)(millis() - _lastActivity);      // time since last activity  
if(_tTime > (_timeout * 1000) && _timeout>0) {disp.fillScreen(0);}
}
void sm::Show() 
{
if(_change)
{
    disp.fillScreen(0);
    disp.setTextColor(1);
    disp.setCursor(0, 0);
    uint8_t cur_x=2;
    if(_title){ disp.setTextSize(tx,ty);//establece el tamaño para el titulo en caso de haber
        if(alignTitle==CENTER || alignTitle==RIGHT)
          {cur_x=(alignTitle==CENTER)?CENTER_H(_opt[0]):RIGHT_H(_opt[0]);}
   disp.setCursor(cur_x, 0);
   disp.print(_opt[0]); }
   disp.setTextSize(ix,iy); //establece el tamaño para los items 
   uint8_t initLine= (_selected<=_max_lines)? (_title)?1:0 : (_selected-_max_lines) +_title ; 
    cur_x=2;
       for (uint8_t i=initLine; i <=_nroItems ; i++) {
    uint8_t  j=(_selected>_max_lines)?(i-initLine)+_title:i;
     if(alignItem==CENTER || alignItem==RIGHT){cur_x=(alignItem==CENTER)?CENTER_H(_opt[i]):RIGHT_H(_opt[i]);}
       disp.setCursor(cur_x, j*(_lineht+_interline));  
      //disp.setCursor(cur_x, (j*_lineht)+_interline);  
       if (i == _selected) {
       disp.setTextColor(0,1);
       disp.print(_opt[i]);
      } else if (i != _selected) {
        disp.setTextColor(1,0);
        disp.print(_opt[i]);
      }
 
}
_change=false;
}
UpdateOff();
}

uint16_t sm::strWidth(String str)
{
 int16_t  x1=0, y1=0; uint16_t w=0, h=0;
 disp.getTextBounds(str.c_str(), disp.getCursorX(),disp.getCursorY(), &x1, &y1, &w, &h); //calc width of string
return w;
}

uint16_t sm::strHeight(String str)
{
 int16_t  x1=0, y1=0;  uint16_t w=0, h=0;
 disp.getTextBounds(str.c_str(), disp.getCursorX(),disp.getCursorY(), &x1, &y1, &w, &h); //calc width of string
return h;
}
#endif

void sm::Pause(bool opt) {  _pause=opt; }

void sm::Down() {  _change=true; _lastActivity = millis();  _selected =(_selected<_nroItems)?_selected + 1:_title;  }
void sm::Up()   {  _change=true; _lastActivity = millis();  _selected =(_selected<(1+_title))?_nroItems:_selected - 1; }


void sm::fullDown() {  _change=true; _lastActivity = millis();  _selected =_nroItems;  }
void sm::fullUp()   {  _change=true; _lastActivity = millis();  _selected =1+_title; }

template <typename T, class tipo> 
void sm::Root(T (&opt), tipo id,bool title)
{
String test=String(id);
byte tam=size(opt);
_root_opt = new txtMenu[tam]; 
for (uint8_t i = 0; i < tam; i++) {_root_opt[i]=opt[i]; }
 
if(isNumeric(test)){_root_id=test.toInt();Assign(_root_opt,_root_id,title);}
else{_root_Id=test;Assign(_root_opt,_root_Id,title);}
}

template <class tipo> 
bool sm::Select(uint8_t sel,tipo id)
{
_change=true;
bool val=false;
String test=String(id);
if(isNumeric(test)){ val=(test.toInt()==_id && _selected==sel)?true:false; }
else{val=(test==_Id && _selected==sel)?true:false;}
return val;
}

void sm::Root()
{  _change=true;
_lastActivity = millis();
if(_root_id!=255)
{Assign(_root_opt,_root_id,_title);}
else if(_root_Id!="") {Assign(_root_opt,_root_Id,_title);}
}
int8_t sm::GetInterline(){ return _interline;}
void sm:: SetAutoOff(uint8_t timeout) { _timeout=timeout; }

void sm::Message(String _text,uint8_t align,int wait)
{
_lastActivity = millis(); 
 uint8_t cur_x=2;
 char text[_text.length()+1]; 
 _text.toCharArray(text,_text.length()+1);
uint8_t  total_lines = stringLineCnt(text);
 #if LIBRARY == U8g2
  disp.setFont(itemFont);
  disp.setFontPosTop();
  disp.clearBuffer();
      uint16_t font_height = STRHeight;
     char buf[LCDWidth/((STRWidth(text)/total_lines))];     
     uint16_t  total_height = (uint16_t)total_lines * (uint16_t)font_height;
 for(uint8_t i = 0; i < total_lines; i++ )
      {
  //copia una linea a la variable buf
  copyStringLine(buf, i, text);
  if(align==CENTER || align==RIGHT ){ cur_x=(align==CENTER)?CENTER_H(buf):RIGHT_H(buf); }
  disp.setCursor(cur_x, ((LCDHeight-total_height)/2)+(i*font_height));
  disp.print(buf);
      }
  disp.sendBuffer();
  delay(wait);

 #elif LIBRARY == GFX
   disp.setTextWrap(false);
   disp.setCursor(0,0);
    disp.fillScreen(0);
    disp.setTextColor(1);
    disp.setTextSize(ix,iy);
   char buf[LCDWidth/((STRWidth(text)/total_lines))];     
   uint16_t font_height=STRHeight("a");
   uint16_t  total_height = (uint16_t)total_lines * (uint16_t)font_height;
   for(uint8_t i = 0; i < total_lines; i++ )
      {
  //copia una linea a la variable buf
  copyStringLine(buf, i, text);
  if(align==CENTER || align==RIGHT ){ cur_x=(align==CENTER)?CENTER_H(buf):RIGHT_H(buf); }
    disp.setCursor(cur_x, ((LCDHeight-total_height)/2)+(i*font_height));
   disp.print(buf);
      }
 #endif  
}
