/**
 * Pràctica 1 - Mètodes Numèrics
 * Autors: Isaac Pizarro i Gina Gardenyes
 * NIUS: 1636421; 1638998;
*/

#include <math.h>
#define PI 3.14159265358979323846


/**
 * Calcula el cosinus i sinus dels múltiples d'un angle.
 * 
 * @param k Número màxim de múltiples a calcular.
 * @param x Angle original en radians.
 * @param c Vector on es guardaran els valors de cosinus calculats.
 * @param s Vector on es guardaran els valors de sinus calculats.
 * 
 * Aquesta funció inicialitza els primers elements de c i s per a cos(0) i sin(0),
 * respectivament, i després utilitza un bucle per calcular el cosinus i sinus
 * de múltiples de x, des de j=1 fins a j=k, emmagatzemant els resultats en c[j] i s[j].
 */
void trigrec0 (int k, double x, double c[], double s[]) {
    c[0] = 1;
    s[0] = 0;

    for(int j=1; j<=k; j++){
        c[j] = cos(j*x); 
        s[j] = sin(j*x);
    }
}


/**
 * Calcula de manera eficient el cosinus i sinus de múltiples d'un angle mitjançant recurrències trigonomètriques.
 * 
 * @param k Número màxim de múltiples a calcular.
 * @param x Angle original en radians.
 * @param c Vector on es guardaran els valors de cosinus calculats.
 * @param s Vector on es guardaran els valors de sinus calculats.
 * 
 * Aquesta funció inicialitza els dos primers elements de c i s amb els valors de cos(0), sin(0),
 * cos(x) i sin(x), respectivament. Després, utilitza un bucle per calcular de manera eficient
 * el cosinus i sinus de múltiples de x fent servir una relació de recurrència que evita el càlcul
 * directe amb funcions trigonomètriques, millorant l'eficiència i potencialment la precisió.
 */
void trigrec1 (int k, double x, double c[], double s[]) {
    c[0] = 1;
    s[0] = 0;
    c[1] = cos(x);
    s[1] = sin(x);
    
    double c_1 = c[1];

    for(int j=1; j<k; j++){
        c[j+1] = 2*c_1*c[j] - c[j-1];
        s[j+1] = 2*c_1*s[j] - s[j-1];
    }
}

/**
 * Calcula de manera més eficient el cosinus i sinus de múltiples d'un angle utilitzant fórmules trigonomètriques.
 * 
 * @param k Número màxim de múltiples a calcular.
 * @param x Angle original en radians.
 * @param c Vector on es guardaran els valors de cosinus calculats.
 * @param s Vector on es guardaran els valors de sinus calculats.
 * 
 * Aquesta funció inicialitza els primers elements de c i s amb els valors de cos(0), sin(0),
 * cos(x) i sin(x), respectivament. Després, utilitza un bucle per calcular el cosinus i sinus
 * de múltiples de x fent servir una relació de recurrència basada en les identitats trigonomètriques
 * per a angles sumats, optimitzant el càlcul i reduint l'error numèric.
 */
void trigrec2 (int k, double x, double c[], double s[]) {
    c[0] = 1;
    s[0] = 0;
    c[1] = cos(x);
    s[1] = sin(x);
    
    double c_1 = c[1];
    double s_1 = s[1];

    for(int j=1; j<k; j++){
        c[j+1] = c_1*c[j] - s_1*s[j];
        s[j+1] = s_1*c[j] + c_1*s[j];
    }
}


/**
 * Calcula el cosinus i el sinus de múltiples d'un angle utilitzant recurrències millorades
 * considerant les diferències entre cosinus i sinus consecutius.
 * 
 * @param k Número màxim de múltiples a calcular.
 * @param x Angle original en radians.
 * @param c Vector on es guardaran els valors de cosinus calculats.
 * @param s Vector on es guardaran els valors de sinus calculats.
 * 
 * Aquesta funció utilitza una tècnica de recurrència per calcular de manera més eficient
 * i precisa el cosinus i sinus de múltiples d'un angle x. La tècnica redueix l'error numèric
 * i millora l'estabilitat dels càlculs en comparació amb els mètodes anteriors.
 * 
 * Inicialitza el primer terme de c i s com a cos(0) = 1 i sin(0) = 0, respectivament.
 * Després, calcula els increments d_c i d_s basats en el sinus de x/2 i utilitza aquests
 * per calcular de forma recorrent els valors de c[j] i s[j] per a j de 1 a k.
 * La recurrència s'ajusta en cada pas basant-se en els valors calculats anteriorment.
 */
void trigrec3 (int k, double x, double c[], double s[]) {
    double d_s, d_c = -2*(sin(x/2)*sin(x/2)); // Calcula la diferència inicial per a cosinus
    
    if((int)(x/PI) % 2 == 0) d_s = sqrt(-d_c*(2+d_c)); // Calcula la diferència inicial per a sinus
    else d_s = -sqrt(-d_c*(2+d_c));

    double t = 2*d_c; // Factor de correcció per als canvis següents

    c[0] = 1;
    s[0] = 0;

    for(int j=1; j<=k; j++){
        c[j] = c[j-1] + d_c; // Actualitza cosinus basant-se en el canvi d_c
        s[j] = s[j-1] + d_s; // Actualitza sinus basant-se en el canvi d_s
        d_c = t*c[j] + d_c; // Recalcula d_c per al proper pas
        d_s = t*s[j] + d_s; // Recalcula d_s per al proper pas
    }
}
