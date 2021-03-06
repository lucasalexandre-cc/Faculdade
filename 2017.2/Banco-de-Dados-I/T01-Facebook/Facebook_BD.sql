CREATE TABLE USUARIO (
	ID_USUARIO	int	NOT NULL,
	DATA_INGRESSO date NOT NULL,
PRIMARY KEY (ID_USUARIO)
);

CREATE TABLE TIMELINE (
	ID_TIMELINE INT NOT NULL,
PRIMARY KEY(ID_TIMELINE)
);

CREATE TABLE PERFIL ( 
	COD_USUARIO	int NOT NULL,
	FOTO_PERFIL varchar(100) NOT NULL DEFAULT 'url_da_foto_default',
	DATA_NASCIMENTO date NOT NULL,
	CIDADE varchar(30),
	ESTADO_CIVIL char(1),
	COD_TIMELINE int NOT NULL,
PRIMARY KEY (COD_USUARIO),
FOREIGN KEY (COD_USUARIO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_TIMELINE) REFERENCES TIMELINE(ID_TIMELINE) ON DELETE CASCADE ON UPDATE RESTRICT
);


CREATE TABLE PAGINA (
	ID_PAGINA int NOT NULL,
	COD_DONO int NOT NULL,
	DATA_CR date NOT NULL,
	FOTO_CAPA varchar(100) NOT NULL DEFAULT 'url_da_foto_default',
	COD_TIMELINE int NOT NULL,
PRIMARY KEY (ID_PAGINA),
FOREIGN KEY (COD_DONO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_TIMELINE) REFERENCES TIMELINE(ID_TIMELINE) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE  GRUPO (
	ID_GRUPO int NOT NULL,
	COD_CRIADOR int NOT NULL,
	FOTO_CAPA varchar(30) NOT NULL,
	DATA_INICIO date NOT NULL,
	COD_TIMELINE int NOT NULL,
PRIMARY KEY (ID_GRUPO),
FOREIGN KEY (COD_TIMELINE) REFERENCES TIMELINE(ID_TIMELINE) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_CRIADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE EVENTO (
	ID_EVENTO int NOT NULL,
	COD_CRIADOR int NOT NULL,
	DATA_INICIO date NOT NULL,
	DATA_FIM date NOT NULL,
	N_CONFIRM int NOT NULL, 
PRIMARY KEY (ID_EVENTO),
FOREIGN KEY (COD_CRIADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE PUBLICACAO (
	ID_PUBLICACAO int NOT NULL,
	TEXTO varchar(500),
	FOTO varchar(200),
	COD_TIMELINE int NOT NULL,
PRIMARY KEY (ID_PUBLICACAO),
FOREIGN KEY (COD_TIMELINE) REFERENCES TIMELINE(ID_TIMELINE) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE MANDA_MSG (
	COD_REMETENTE int NOT NULL,
	COD_DESTINATARIO int NOT NULL,
	TEXTO varchar(500),
	FOTO varchar(200),
	DATA_ENVIO date NOT NULL,
PRIMARY KEY (COD_REMETENTE, COD_DESTINATARIO, DATA_ENVIO),
FOREIGN KEY (COD_REMETENTE) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_DESTINATARIO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE AMIZADE (
	COD_REMETENTE int NOT NULL,
	COD_DESTINATARIO int NOT NULL,
	DATA_INICIO_AM date NOT NULL,
PRIMARY KEY (COD_REMETENTE, COD_DESTINATARIO),
FOREIGN KEY (COD_REMETENTE) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_DESTINATARIO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT
);

CREATE TABLE CONFIRMA_PRESENCA (
	COD_USUARIO int NOT NULL,
	COD_EVENTO int NOT NULL,
	DATA_PRESENCA date NOT NULL,
PRIMARY KEY (COD_USUARIO, COD_EVENTO),
FOREIGN KEY (COD_USUARIO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_EVENTO) REFERENCES EVENTO(ID_EVENTO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table CURTE (
	COD_CURTIDOR int NOT NULL,
	COD_PUBLICACAO int NOT NULL,
	PRIMARY KEY (COD_CURTIDOR, COD_PUBLICACAO),
	FOREIGN KEY (COD_CURTIDOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
	FOREIGN KEY (COD_PUBLICACAO) REFERENCES PUBLICACAO(ID_PUBLICACAO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table PUBLICA (
	COD_PUBLICADOR int NOT NULL,
	COD_PUBLICACAO int NOT NULL,
	PRIMARY KEY (COD_PUBLICACAO),
	FOREIGN KEY (COD_PUBLICADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
	FOREIGN KEY (COD_PUBLICACAO) REFERENCES PUBLICACAO(ID_PUBLICACAO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table COMENTA (
	COD_COMENTARIO int NOT NULL,
	COD_PUBLICADOR int NOT NULL,
	COD_PUBLICACAO int NOT NULL,
	texto varchar(500) NOT NULL,
	PRIMARY KEY (COD_COMENTARIO),
	FOREIGN KEY (COD_PUBLICADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
	FOREIGN KEY (COD_PUBLICACAO) REFERENCES PUBLICACAO(ID_PUBLICACAO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table PARTICIPA_GRUPO ( 
	COD_USUARIO	int NOT NULL,
	COD_GRUPO	int NOT NULL,
	DATA_ENTRADA_GRUPO date NOT NULL,
PRIMARY KEY (COD_USUARIO, COD_GRUPO),
FOREIGN KEY (COD_USUARIO) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_GRUPO) REFERENCES GRUPO(ID_GRUPO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table ADMINISTRA_GRUPO ( 
	COD_ADMINISTRADOR int NOT NULL,
	COD_GRUPO	int NOT NULL,
	DATA_ENTRADA_GRUPO date NOT NULL,
PRIMARY KEY (COD_ADMINISTRADOR, COD_GRUPO),
FOREIGN KEY (COD_ADMINISTRADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_GRUPO) REFERENCES GRUPO(ID_GRUPO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table CURTE_PAGINA ( 
	COD_CURTIDOR int NOT NULL,
	COD_PAGINA	int NOT NULL,
PRIMARY KEY (COD_CURTIDOR, COD_PAGINA),
FOREIGN KEY (COD_CURTIDOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_PAGINA) REFERENCES PAGINA(ID_PAGINA) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table ADMINISTRA_PAGINA ( 
	COD_ADMINISTRADOR int NOT NULL,
	COD_PG	int NOT NULL,
PRIMARY KEY (COD_ADMINISTRADOR, COD_PG),
FOREIGN KEY (COD_ADMINISTRADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_PG) REFERENCES PAGINA(ID_PAGINA) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table COMPARTILHA (
	COD_COMPARTILHADOR int NOT NULL,
	COD_PUBLICACAO int NOT NULL,
PRIMARY KEY (COD_COMPARTILHADOR, COD_PUBLICACAO),
FOREIGN KEY (COD_COMPARTILHADOR) REFERENCES USUARIO(ID_USUARIO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_PUBLICACAO) REFERENCES PUBLICACAO(ID_PUBLICACAO) ON DELETE CASCADE ON UPDATE RESTRICT
);

create table PUBLICA_EM (
	COD_PUBLICACAO int NOT NULL,
	COD_TIMELINE int NOT NULL,
PRIMARY KEY (COD_PUBLICACAO, COD_TIMELINE),
FOREIGN KEY (COD_PUBLICACAO) REFERENCES PUBLICACAO(ID_PUBLICACAO) ON DELETE CASCADE ON UPDATE RESTRICT,
FOREIGN KEY (COD_TIMELINE) REFERENCES TIMELINE(ID_TIMELINE) ON DELETE CASCADE ON UPDATE RESTRICT
);