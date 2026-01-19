//Estrarre in val (unsigned char [8 bit]) il valore dal 16 al 23 esimo bit in TC
val = (LPC_TIM1->TC & (255 << 16)) >> 16;

//Rappresentare sui led il valore res di 32 bit, 8 bit alla volta, partendo da LSB
aus = ((res & (255 << (8 * position)))) >> (8 * position);

//stampare val2 sui primi 4 led (MSB) e val1 sugli ultimi 4 led (LSB)
val2 = val2 << 4;
ledV = val2 | val1;