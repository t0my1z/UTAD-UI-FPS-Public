Memoria de la actividad -- Tomás Rodrigo Castrillo

Barra de vida del jugador
Para hacer que la ProgressBar muestre el valor de Health, opte por usar delegados a los que el widget 
se suscribe en su método Setup, que llama el PlayerHUD en su método de Setup.
El FPSCharacter tiene un método SetHealth, que lanza el delegado. Tengo un método aparte GetDamaged, 
que llama a SetHealth, pero aparte lanza otro delegado exclusivo de recibir daño. 
Hice esta diferenciación para que el marcador de daño de pantalla solo salga al recibir daño.

Crosshair Dinámico
Siguiendo la misma lógica de eventos, el crosshair se suscribe a dos eventos del WeaponComponent. 
El primer evento se llama cuando el jugador apunta a un enemigo, y se llama una vez cuando empieza a apuntar a un enemigo, 
y otra vez cuando deja de apuntar a un enemigo. 
El crosshair cambia de color, dependiendo del estado.
El otro evento se llama cada vez que se dispara el arma, y el crosshair hace una WidgetAnimation.

Marcador de daño en pantalla
El widget está suscrito al evento OnDamaged del FPSCharacter, 
y al recibir daño hace una animación que hace que sea visible durante unos segundos una imagen transparente de color rojizo.
Dependiendo del porcentaje de vida, usa un color u otro, usando un mapa para esto.

Pantalla Splash
Simple widget que aparece al empezar el juego, y en unos segundos desaparece.

Árbol de Habilidades
Mi idea para el skillTree era hacer una UI que leyera de una DataTable y crease la UI correspondiente, y eso es precisamente lo que hace.
De esta forma, si hay que añadir o cambiar habilidades, se puede hacer fácilmente desde ahí.
Utilizo un componente llamado SkillTreeComponent que es en el que decides que DataTable, y que columna de está, tiene que utilizar para crear la UI.
También tiene los inputs que se usan para navegar por la UI usando el EnhancedInputSystem de unreal.
He intentado mantener separado todo lo que he podidola lógica de gameplay y la de UI, haciendo que el componente sea el encargado de leer o
 cambiar cosas como los SkillPoints del player, y que la UI sea algo que simplemente lee y se actualiza.
