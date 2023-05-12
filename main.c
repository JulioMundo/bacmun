#include<18F4550.H>
#fuses HSPLL, PLL5, USBDIV, NOWDT, CPUDIV1, NOPROTECT, NODEBUG, NOPBADEN, NOLVP, NOVREGEN, NOPUT, NOBROWNOUT//2OMHZ
#use delay(clock=8MHz, crystal)
//#use fast_io(A)
#use standard_io(A)
#define DHT11_PIN PIN_A1
#use I2C(MASTER, SDA=PIN_B0, SCL=PIN_B1, SLOW)
#define LCD_ENABLE_PIN  PIN_C0
#define LCD_RS_PIN      PIN_C1
#define LCD_RW_PIN      PIN_C2
#define LCD_DATA4       PIN_B4
#define LCD_DATA5       PIN_B5
#define LCD_DATA6       PIN_B6
#define LCD_DATA7       PIN_B7
#include <lcd.c>
#include <DHT11.c>
#include <stdio.h>
#include"KBD4x4.c"
#include<DS1307.c>
#include <stddef.h>
int Tempprogramada;
int data_ok = 0;
float humedad, temperatura;
int dia=19, mes=04, an=23, dow=5;
int hora=13,min=30,seg=0;

#include <string.h>
#include <stdlib.h>//array

int concat(int num){
    static int aux = 0;
    if(num!=-1){
        aux =(aux * 10) + num  ;
    }else{
        aux=0;}
    return aux;
}

int getValue(){
    concat(-1);
    char tecla;
    char numbers[2];
    int count = 0, num;

    do{
        tecla=kbd_getc();
        if(tecla!=0) {
            if(tecla!='B'){
                numbers[count] = tecla;;
                lcd_putc(tecla);
                delay_ms(50);
                count++;

                if (count == 2 && tecla!='B') {

                    for (int x = 0; x < sizeof(numbers); x++) {
                        num = concat(numbers[x] - 48);
                    }
                    lcd_putc("\f");
                    lcd_gotoxy(1, 1);
                    lcd_putc("A=ok B=back");
                    lcd_gotoxy(1, 2);
                    printf(lcd_putc, "numero:%02u", num);
                    delay_ms(50);
                }
            }else {
                num=0;
                count=0;
                lcd_putc("\f");
                concat(-1);
            }
        }

    }  while (tecla != 'A');

    return  num;
}


void notExist(){
    lcd_putc("\f");
    lcd_gotoxy(1,1);
    printf(lcd_putc,"Upss! incorrecto");

}

void alarm( int diaprogramadoc1,int mesprogramadoc1,int yearprogramadoc1,int horaprogramadac1,int minprogramadoc1,int segprogramadoc1){

    ds1307_get_date(dia, mes, an, dow);//obtiene fecha actual
    ds1307_get_time(hora, min, seg);//obtiene hora actual

    if(dia==diaprogramadoc1&&mes==mesprogramadoc1&&an==yearprogramadoc1&&hora==horaprogramadac1&&min==minprogramadoc1&&seg==segprogramadoc1){
        output_high(PIN_A0);
        lcd_putc("\f");
        lcd_gotoxy(1,1);
        printf(lcd_putc,"fecha:%02u/%02u/20%02u",diaprogramadoc1,mesprogramadoc1,yearprogramadoc1);
        lcd_gotoxy(1,2);
        printf(lcd_putc,"hora: %02u:%02u:%02u",horaprogramadac1,minprogramadoc1,segprogramadoc1);
        delay_ms(10000);
        output_low(PIN_A0);
        lcd_putc("\f");
        lcd_gotoxy(1,1);
        lcd_putc("1=celda 2=temp       ");
        lcd_gotoxy(1,2);
    }
}

void dht11(int *data_ok){
    data_ok = DHT11_read_data(&humedad, &temperatura);

    if (data_ok == 1) {
        delay_ms(1500);
        lcd_putc("\f");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "H=%0.1f%%", humedad);
        lcd_gotoxy(8, 2);
        printf(lcd_putc, "T=%0.1fC", temperatura);
    } else {
        delay_ms(1500);
        lcd_putc("\f");
        lcd_gotoxy(2, 1);
        lcd_putc("No Conectado");
    }
    delay_ms(1000);
}


void main(void){


    set_tris_a(0x00);
    output_a(0x00);

    int diaprogramadoc1,mesprogramadoc1,yearprogramadoc1,horaprogramadac1,minprogramadoc1, segprogramadoc1;
    ds1307_set_date_time(dia,mes,an,dow,hora,min,seg);
    char tecla;
    char contra[2]; //aqui se guardan las teclas del teclado

    //----------------Array to save data about place
    int filas=2, columnas=6;
    int array[2][6];
    //---------------------------------------------------

    int direccion=0, opt=0;
    lcd_init();
    lcd_putc("\f");
    delay_ms(1500); //sin este tiempo de espera no jala porque no deja arrancar el lcd
    kbd_init();


    while(true) {

        //para temperatura inicio
//        dht11(&data_ok);
        //temperatura final

//        alarm(diaprogramadoc1, mesprogramadoc1, yearprogramadoc1, horaprogramadac1, minprogramadoc1, segprogramadoc1);


        tecla = kbd_init();
        
        if (tecla != 0){
            if (tecla == 'C'){
                delay_ms(1500);
                lcd_putc("\f");
                lcd_gotoxy(2, 1);
                lcd_putc("Comenzaste , menu");
            }else{
                notExist(); 
            }
        }else{
            delay_ms(1500);
            lcd_putc("\f");
            lcd_gotoxy(2, 1);
            lcd_putc("Verificando temperatura y alarmas");
        }

       
    }

}
