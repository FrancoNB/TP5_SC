# Trabajo final de la materia de Sistemas de Computación 2023 

Implementación de un modulo para el kernel de Linux que permite la lectura de sensores [*DHT11*](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf) y [*TFMINI*](https://alicliimg.clewm.net/476/457/1457476/1502760306607344e88e353c263a4b22b3680f6a8be261502760289.pdf) por medio de una interfaz de puerto serie con el adaptador [*CP210x*](https://www.sparkfun.com/datasheets/IC/cp2102.pdf). También se implementa una aplicación a nivel de usuario que hace uso del driver.

### Integrantes:
- **Lencina, Aquiles Benjamin**
- **Robledo, Valentin**
- **Bottini, Franco Nicolas**

### Grupo: **CLovers**

## Compilación

Para compilar el proyecto lo primero es clonar el repositorio:

```bash
$ git clone https://github.com/FrancoNB/TP5_SC.git
```

Con el repositorio ya clonado, se debe ingresar a la carpeta del proyecto:

```bash
$ cd TP5_SC
```

Una vez hecho esto, se pueden comenzar a compilar los distintos módulos del proyecto.

### Modulo del kernel

Para compilar y cargar el modulo del kernel se debe acceder al directorio `/driver` y ejecutar el makefile:

```bash
$ cd driver
$ make
```

Como resultado obtenemos el archivo `sensors_driver.ko` que es el modulo compilado en el directorio `/bin`. Una vez compilado el modulo, se puede cargar al kernel con el siguiente comando:

```bash
$ sudo insmod bin/sensors_driver.ko
```

Si todo salio bien, se deben haber detectado los sensores conectados al dispositivo y generado sus correspondientes rutas de acceso en `/dev`. Si se conectan nueves dispositivos posterior a la carga del modulo, estos serán detectados y mapeados automáticamente, del mismo modo se des-mapean los dispositivos que son desconectados. Se puede verificar el correcto funcionamiento del modulo analizando los mensajes del kernel:

```bash
$ dmesg
```

Finalmente, si se desea descargar el modulo del kernel se debe ejecutar el siguiente comando:

```bash
$ sudo rmmod sensors_driver
```

**Nota:** Para compilar el modulo es necesario tener instaladas las herramientas de compilación del kernel. En caso de no tenerlas, se pueden instalar con el siguiente comando:

```bash
$ sudo apt-get install linux-headers-$(uname -r)
```

### Aplicacion servidor

Para compilar la aplicación servidor se debe acceder al directorio `/server` y ejecutar:

```bash
$ cd server
$ cmake .
$ make
```

Como resultado obtenemos el archivo `server` en el directorio `/bin`. Para ejecutar la aplicación se debe ejecutar:

```bash
$ sudo ./bin/server
```

**Nota:** La aplicación servidor debe ejecutarse con permisos de superusuario para poder acceder a los dispositivos mapeados en `/dev`.

### Aplicacion cliente

Para compilar la aplicación cliente se debe acceder al directorio `/app` y ejecutar:

```bash

```

## Funcionamiento general

El modulo del kernel se encarga de mapear y dar soporte a los sensores conectados por medio del puente usb-serial, generando dispositivos en el directorio `/dev` fáciles de leer en aplicaciones de nivel de usuario por medio de operaciones con ficheros. 

El server corre a nivel de usuario sobre el dispositivo donde se encuentran conectados físicamente los sensores y hace uso del driver para obtener las lecturas de los mismos. Luego, expone las lecturas disponibles a través de un sockect ipv4 que permite el acceso a los datos de manera remota y soporta múltiples conexiones. 

Finalmente, la aplicación cliente también se ejecuta a nivel usuario y se conecta a la aplicación servidor permitiendo al usuario visualizar los datos de los sensores en tiempo real y de manera sencilla.

## Uso

## Licencia

[Gnu GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html)
