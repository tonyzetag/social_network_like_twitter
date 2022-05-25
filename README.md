# social_network_like_twitter
Práctica universitaria entregable, proyecto TAD en C++, creación de una red social estilo twitter.

## Enunciado
Desarrollar un TAD para gestionar un usuario de la red social Twitter. El usuario debe poder mantener
una lista de usuarios (nombres de usuario) a los que sigue en la red social, una lista de usuarios que son
sus seguidores y, por último, una lista de tweets.

Un tweet comienza con una serie de datos numéricos, correspondientes al día, mes, año, hora, minuto
y segundo en el que se escribi´o el tweet, y continúa con un cadena, con un máximo de 140 caracteres,
correspondiente al tweet. Ejemplos de tweets, del usuario ada_lovelace podrían ser los siguientes:

5 2 2014 9 10 1 Me encanta la maquina de @carlos_babbage, es mi favorita con diferencia
5 2 2014 9 11 2 Creo que puedo escribir algun algoritmo para la maquina de
@carlos_babbage, no me parece dificil @blas_pascal
5 2 2014 19 1 10 He escrito un algoritmo para sumar numeros complejos con la maquina
de @carlos_babbage, creo que me hare famosa

Una vez desarrollado el TAD UsuarioTwitter debe implementarse un programa principal, lo más sencillo
posible, para probar su correcto funcionamiento.

Completar la clase UsuarioTwitter añadiendo los tipos necesarios para la gestión de menciones entre los
usuarios. Una mención se produce cuando un usuario incluye el nombre de otro usuario de la red en uno
de sus tweets. Por ejemplo, en la lista de tweets del usuario ada_lovelace (que tiene solo 3 tweets) 
se producen menciones a dos usuarios: carlos_babbage, en los tweets 0, 1 y 2, y blas_pascal, en el
tweet 1.

Un objeto de la clase UsuarioTwitter guardará una lista con las menciones que otros usuarios hacen de
él/ella en sus tweets. Para cada mención, se guardará el nombre del usuario que la realizó y el número
de tweet donde lo hizo. Así, dado el ejemplo anterior, el usuario carlos_babbage deberá guardar en
su lista de menciones tres menciones realizadas por el usuario ada_lovelace: {{ {"ada_lovelace", 0},
{"ada_lovelace", 1}, {"ada_lovelace", 2} }}.
