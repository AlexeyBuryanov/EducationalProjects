-- Script by: Alexey Bur'yanov, 27.06.2017

-- Создание БД "Учет договоров страхования" (InsuranceContractsAB).
-- Создание в ней таблиц: КЛИЕНТЫ, АГЕНТЫ, ВИДЫ СТРАХОВАНИЯ,
--                        ДОГОВОРА СТРАХОВАНИЯ, РАСТОРГНУТЫЕ ДОГОВОРА СТРАХОВАНИЯ.
-- Заполнение этих таблиц данными.

-- Скорректируйте правильный путь к фото, иначе сценарий не отработает.
-- Может есть более элегантный способ загрузки изображения, но я нашёл только этот.
-- Для загрузки изображений в базу используем "Большой двоичный объект (BLOB)".

-- InsuranceContractsAB
IF DB_ID('InsuranceContractsAB') IS NOT NULL BEGIN
	PRINT('Создание БД InsuranceContractsAB: БД уже существует!');
	PRINT('Пересоздание...');
	USE master;
	DROP DATABASE InsuranceContractsAB;
	CREATE DATABASE InsuranceContractsAB;
	PRINT('Создание БД InsuranceContractsAB: успешно.');
END ELSE BEGIN
	CREATE DATABASE InsuranceContractsAB;
	PRINT('Создание БД InsuranceContractsAB: успешно.');
END
GO
USE InsuranceContractsAB;
GO


CREATE TABLE Clientage( -- КЛИЕНТЫ
	Id          INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_Clientage PRIMARY KEY,
	CSecondName NVARCHAR(60)      NOT NULL, -- Фамилия клиента
	CFirstName  NVARCHAR(60)      NOT NULL, -- Имя
	CMiddleName NVARCHAR(60)      NOT NULL, -- Отчество
	CPassport   NVARCHAR(10)      NOT NULL, -- Серия и номер паспорта
	CDiscount   FLOAT             NOT NULL, -- Процент скидки
	CPhoto      IMAGE             NULL,     -- Фото клиента
);
CREATE TABLE Agents( -- АГЕНТЫ
	Id          INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_Agents PRIMARY KEY,
	ASecondName NVARCHAR(60)      NOT NULL, -- Фамилия страхового агента
	AFirstName  NVARCHAR(60)      NOT NULL, -- Имя
	AMiddleName NVARCHAR(60)      NOT NULL, -- Отчество
	AReward     FLOAT             NOT NULL, -- Процент вознаграждения 
	APhoto      IMAGE             NULL,     -- Фото агента
);
CREATE TABLE TypesInsurance( -- ВИДЫ СТРАХОВАНИЯ
	Id     INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_TypesInsurance PRIMARY KEY,
	[Type] NVARCHAR(60)      NOT NULL, -- Вид страхования
	Tariff FLOAT             NOT NULL, -- Тариф на данный вид страховки
);
CREATE TABLE Contracts( -- ДОГОВОРА СТРАХОВАНИЯ
	Id                INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_Contracts PRIMARY KEY,
	IdClient          INT NOT NULL CONSTRAINT FK_Contracts_Clientage -- Клиент
			          FOREIGN KEY REFERENCES Clientage(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	IdAgent           INT NOT NULL CONSTRAINT FK_Contracts_Agents    -- Агент
			          FOREIGN KEY REFERENCES Agents(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	IdTypeInsurance   INT NOT NULL CONSTRAINT FK_Contracts_TypesInsurance -- Вид страховки
			          FOREIGN KEY REFERENCES TypesInsurance(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	SumInsurance      MONEY NOT NULL CHECK(SumInsurance >= 0),            -- Сумма страховки
	DateConclusion    DATE  NOT NULL									  -- Дата заключения договора
);
CREATE TABLE CanceledContracts( -- РАСТОРГНУТЫЕ ДОГОВОРА СТРАХОВАНИЯ
	Id                INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_CanceledContracts PRIMARY KEY,
	IdClient          INT NOT NULL CONSTRAINT FK_CanceledContracts_Clientage -- Клиент
			          FOREIGN KEY REFERENCES Clientage(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	IdAgent           INT NOT NULL CONSTRAINT FK_CanceledContracts_Agents    -- Агент
			          FOREIGN KEY REFERENCES Agents(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	IdTypeInsurance   INT NOT NULL CONSTRAINT FK_CanceledContracts_TypesInsurance -- Вид страховки
			          FOREIGN KEY REFERENCES TypesInsurance(Id)
			          ON UPDATE CASCADE
			          ON DELETE CASCADE,
	SumInsurance      MONEY NOT NULL CHECK(SumInsurance >= 0),            -- Сумма страховки
	DateConclusion    DATE  NOT NULL,									  -- Дата заключения договора
	TerminationSign   NVARCHAR(200) NOT NULL							  -- Признак расторжения договора
);
GO


INSERT INTO Clientage (CSecondName, CFirstName, CMiddleName, CPassport, CDiscount, CPhoto) VALUES
	('Давыдова',    'Лидия',      'Владиславовна', 'ВК387652', 0.5, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Давыдова Лидия Владиславовна.jpg',   SINGLE_BLOB) AS T)),
	('Чаурина',     'Злата',      'Петровна',      'ВН984474', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Чаурина Злата Петровна.jpg',         SINGLE_BLOB) AS T)),
	('Федотов',     'Ювеналий',   'Вениаминович',  'ЛМ111111', 0.5, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Федотов Ювеналий Вениаминович.jpg',  SINGLE_BLOB) AS T)),
	('Львова',      'Степанида',  'Борисовна',     'ДН098175', 0.2, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Львова Степанида Борисовна.jpg',     SINGLE_BLOB) AS T)),
	('Никифорова',  'Элла',       'Богдановна',    'ВК888888', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Никифорова Элла Богдановна.jpg',     SINGLE_BLOB) AS T)),
	('Фомов',       'Сигизмунд',  'Тимурович',     'ШК929292', 0.5, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Фомов Сигизмунд Тимурович.jpg',      SINGLE_BLOB) AS T)),
	('Васильев',    'Мина',       'Матвеевич',     'ВН999999', 0.4, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Васильев Мина Матвеевич.jpg',        SINGLE_BLOB) AS T)),
	('Ахметзянов',  'Илья',       'Богданович',    'ЗК000000', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Ахметзянов Илья Богданович.jpg',     SINGLE_BLOB) AS T)),
	('Андреева',    'Аглая',      'Ярославовна',   'ОР666666', 0.3, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Андреева Аглая Ярославовна.jpg',     SINGLE_BLOB) AS T)),
	('Кравченко',   'Вероника',   'Игоревна',      'ЛМ857261', 0.2, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Кравченко Вероника Игоревна.jpg',    SINGLE_BLOB) AS T)),
	('Дмитриева',   'Луиза',      'Максимовна',    'ФН561285', 0.3, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Дмитриева Луиза Максимовна.jpg',     SINGLE_BLOB) AS T)),
	('Баландина',   'Кларисса',   'Тимофеевна',    'ДЛ572652', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Баландина Кларисса Тимофеевна.jpg',  SINGLE_BLOB) AS T)),
	('Лапина',      'Клементина', 'Ильинична',     'ЭХ000000', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Лапина Клементина Ильинична.jpg',    SINGLE_BLOB) AS T)),
	('Городнов',    'Валерьян',   'Аркадьевич',    'ИЕ175829', 0.4, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Городнов Валерьян Аркадьевич.jpg',   SINGLE_BLOB) AS T)),
	('Жукова',      'Ярослава',   'Васильевна',    'ВН152914', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Жукова Ярослава Васильевна.jpg',     SINGLE_BLOB) AS T)),
	('Рустамова',   'Нина',       'Ильинична',     'ЕК186729', 0.5, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Рустамова Нина Ильинична.jpg',       SINGLE_BLOB) AS T)),
	('Журавель',    'Владлена',   'Семеновна',     'ВН309518', 0.1, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Журавель Владлена Семеновна.jpg',    SINGLE_BLOB) AS T)),
	('Федотова',    'Владилена',  'Платоновна',    'ВН423445', 0.4, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Федотова Владилена Платоновна.jpg',  SINGLE_BLOB) AS T)),
	('Сысолятина',  'Альбина',    'Евгеньевна',    'ВН641308', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Сысолятина Альбина Евгеньевна.jpg',  SINGLE_BLOB) AS T)),
	('Журавлёва',   'Флорентина', 'Матвеевна',     'ВК678179', 0.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoClientage\Журавлёва Флорентина Матвеевна.jpg', SINGLE_BLOB) AS T));
GO
INSERT INTO Agents (ASecondName, AFirstName, AMiddleName, AReward, APhoto) VALUES
	('Холодкова',    'Лилиана',  'Егоровна',      7.5,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Холодкова Лилиана Егоровна.jpg',         SINGLE_BLOB) AS T)),
	('Герасимов',    'Борислав', 'Антонович',     11.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Герасимов Борислав Антонович.jpg',       SINGLE_BLOB) AS T)),
	('Фролова',      'Аделаида', 'Игоревна',      6.8,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Фролова Аделаида Игоревна.jpg',          SINGLE_BLOB) AS T)),
	('Пономарёва',   'Вера',     'Ярославовна',   10.0, (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Пономарёва Вера Ярославовна.jpg',        SINGLE_BLOB) AS T)),
	('Петрова',      'Любомила', 'Богдановна',    5.1,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Петрова Любомила Богдановна.jpg',        SINGLE_BLOB) AS T)),
	('Борисов',      'Никодим',  'Артемович',     6.4,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Борисов Никодим Артемович.jpg',          SINGLE_BLOB) AS T)),
	('Стручкова',    'Диана',    'Александровна', 6.0,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Стручкова Диана Александровна.jpg',      SINGLE_BLOB) AS T)),
	('Недашковский', 'Светозар', 'Валентинович',  5.0,  (SELECT BulkColumn FROM OPENROWSET (BULK 'D:\PhotoAgents\Недашковский Светозар Валентинович.jpg', SINGLE_BLOB) AS T));
GO
INSERT INTO TypesInsurance ([Type], Tariff) VALUES
	('Жилищное страхование',                                    3.0),
	('Страхование транспортных средств',                        2.2),
	('Страхование профессиональной ответственности',            1.5),
	('Страхование ответственности за нанесение вреда экологии', 4.2),
	('Накопительное страхование жизни, пенсионное страхование', 4.4),
	('Страхование от несчастного случая',                       1.1),
	('Медицинское страхование',                                 2.9),
	('Страхование невыполнения финансовых обязательств',        5.0),
	('Страхование политических рисков',                         3.8);
GO
INSERT INTO Contracts (IdClient, IdAgent, IdTypeInsurance, SumInsurance, DateConclusion) VALUES
	(1,  1, 1, 200000, '01.01.2012'),
	(2,  2, 2, 500000, '01.04.2010'),
	(3,  3, 3, 890000, '16.07.2015'),
	(4,  4, 4, 567000, '21.08.2016'),
	(5,  5, 5, 100100, '26.01.2004'),
	(6,  6, 6, 354897, '31.12.2009'),
	(7,  7, 7, 186533, '25.09.2011'),
	(8,  8, 8, 888888, '14.02.2015'),
	(9,  1, 9, 999999, '17.03.2015'),
	(10, 2, 1, 50000,  '10.04.2014'),
	(11, 3, 2, 50000,  '11.05.2014'),
	(12, 4, 3, 75000,  '01.06.2017'),
	(13, 5, 4, 40000,  '19.07.2017'),
	(14, 6, 5, 55000,  '27.12.2017'),
	(15, 7, 6, 89000,  '10.12.2017'),
	(16, 8, 7, 999000, '04.12.2015'),
	(17, 1, 8, 899000, '19.06.2012'),
	(18, 2, 9, 65000,  '30.07.2008'),
	(19, 3, 1, 42000,  '31.07.2011'),
	(20, 4, 2, 40999,  '01.08.2016'),
	(1,  5, 3, 75000,  '13.09.2017'),
	(3,  6, 4, 80555,  '19.03.2016'),
	(5,  7, 5, 200000, '17.05.2014'),
	(7,  8, 6, 97574,  '15.04.2016'),
	(9,  1, 7, 11000,  '07.02.2009'),
	(11, 3, 8, 78000,  '10.10.2008'),
	(13, 5, 9, 101000, '12.10.2002'),
	(15, 7, 2, 67876,  '27.01.2012'),
	(17, 1, 4, 45421,  '12.01.2016'),
	(19, 1, 6, 30000,  '07.01.2017');
GO


IF OBJECT_ID('ContractsLog') IS NULL BEGIN
	CREATE TABLE ContractsLog( -- ЖУРНАЛ ДОГОВОРОВ
		Id             INT IDENTITY(1,1) NOT NULL CONSTRAINT PK_ContractsLog PRIMARY KEY,
		Msg            NVARCHAR(80) NOT NULL, -- Сообщение
		DateOperation  DATETIME     NOT NULL, -- Дата и время операции
		KindOperation  NVARCHAR(40) NOT NULL  -- Вид операции
	);
END
GO

-- Триггеры контрактов (договоров страхования)
CREATE TRIGGER onDeleteContracts
ON dbo.Contracts
FOR DELETE
AS
BEGIN
    DECLARE @counter INT;
    SELECT  @counter = COUNT(*)
    FROM    deleted;
    INSERT INTO dbo.ContractsLog (Msg, DateOperation, KindOperation) VALUES
    ('Удалено договоров' + STR(@counter), GETDATE(), 'Delete');
END;
GO

CREATE TRIGGER onInsertContracts
ON dbo.Contracts
FOR INSERT
AS
BEGIN
    DECLARE @counter INT;
    SELECT  @counter = COUNT(*)
    FROM    inserted;
    INSERT INTO dbo.ContractsLog (Msg, DateOperation, KindOperation) VALUES
    ('Добавлено договоров' + STR(@counter), GETDATE(), 'Insert');
END;
GO

CREATE TRIGGER onUpdateContracts
ON dbo.Contracts
FOR UPDATE
AS
BEGIN
    INSERT INTO dbo.ContractsLog (Msg, DateOperation, KindOperation) VALUES
    ('Изменено договоров' + STR(@@rowcount), GETDATE(), 'Update');
END;
GO