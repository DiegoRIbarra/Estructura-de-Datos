# Pilas y Colas

## ¿Que son?

### Colas

Las colas son una estructura de dato lineal que se caracteriza por se una estructura **First-in-First-out (FIFO)** Esto significa que funcionan como una cola de personas en una panadería: la primera persona en llegar a la panadería será la primera en ser atendida y así sucesivamente hasta vaciar la cola.

Para poder hacer uso de ellas se tiene que importar el modulo **queue**

```c++
    queue<int> cola;
```

las colas solamente pueden guardar objetos de una clase creada por el usuario o estandar, en este ejemplo esta cola solamente podra guardar datos de tipo int.

Las colas tienen una serie de operaciones que se pueden realizar con ellas:

- Insertar elementos: para insertar un elemento al final de la cola, podemos usar la función `push()`.

- Eliminar elementos: para quitar el elemento del principio de la cola, podemos usar la función `pop()`.

- Ver cuál es el primer elemento de la cola: para ver cuál es este elemento, podemos usar la función `front()`. Esto es muy útil, ya que `pop()` únicamente quitará el primer elemento de la cola, pero no nos dirá cuál es en c++. 

- Ver cuál es el último elemento de la cola: hay un equivalente de la función `front()` para el final de la cola, la función `back()`.

- Ver cuántos elementos tiene la cola: para saber esto, podemos utilizar la función `size()`. Además, podremos saber si la cola está vacía con la función `empty()`.

### Pilas 

las pilas al igual que las colas son estructuras lineales pero con la diferencia de que son **last-in-first-out (LIFO)** 

Esto significa que funcionan como un montón de cartas donde no solo levantarás siempre la carta que está arriba del todo del montón, pero también colocarás siempre las cartas arriba del todo del montón.

para poder usar las pilar se debe importar el modulo **stack**
```c++
    stack<int> pila;
```

Las colas tienen una serie de operaciones que se pueden realizar con ellas:

- Insertar elementos: para insertar un elemento en la parte de arriba de la pila, podemos usar la función `push()`.

- Eliminar elementos: para quitar el elemento de arriba del todo de la pila, podemos usar la función `pop()`.

- Ver cuál es el elemento de arriba del todo de la pila: para ver cuál es este elemento, podemos usar la función `top()`. Esto es muy útil, ya que `pop()` únicamente quitará el primer elemento de la pila, pero no nos dirá cuál es. 

- Ver cuántos elementos tiene la pila: para saber esto, podemos utilizar la función `size()`. Además, podremos saber si la pila está vacía con la función `empty()`.

### Priority FIFO

El ingreso y ¿orden? de los elementos se hace en base a la prioridad que tenga, (escala de prioridad)  (investigar)




