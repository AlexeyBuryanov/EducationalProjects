-- Script by: Alexey Bur'yanov, 28.06.2017
-- Source   : http://edu.tltsu.ru/er/book_view.php?book_id=2790&page_id=31381 

-- Создание процедур

USE InsuranceContractsAB;
GO

-- Для DataSet операций
CREATE PROCEDURE sp_CreateClient
    @Id INT OUT,
    @secondName NVARCHAR(60),
    @firstName NVARCHAR(60),
    @middleName NVARCHAR(60),
    @passport NVARCHAR(10),
    @discount FLOAT,
    @photo IMAGE
AS
BEGIN
    INSERT INTO Clientage (CSecondName,
                           CFirstName,
                           CMiddleName,
                           CPassport,
                           CDiscount,
                           CPhoto)
    VALUES (@secondName, @firstName, @middleName, @passport, @discount, @photo);

    SET @Id = SCOPE_IDENTITY();
END;
GO
-- Для DataSet операций
CREATE PROCEDURE sp_CreateAgent
    @Id INT OUT,
    @secondName NVARCHAR(60),
    @firstName NVARCHAR(60),
    @middleName NVARCHAR(60),
    @reward FLOAT,
    @photo IMAGE
AS
BEGIN
    INSERT INTO Agents (ASecondName,
                        AFirstName,
                        AMiddleName,
                        AReward,
                        APhoto)
    VALUES (@secondName, @firstName, @middleName, @reward, @photo);

    SET @Id = SCOPE_IDENTITY();
END;
GO

-- ================================= ЗАПРОСЫ
-- Выбирает из таблицы КЛИЕНТЫ информацию о клиентах, для которых процент скидки равен 0.5 %
CREATE PROCEDURE sp_Request01
AS
BEGIN
    SELECT Id,
           CSecondName,
           CFirstName,
           CMiddleName,
           CPassport,
           CDiscount,
           CPhoto
    INTO   #TempTable
      FROM dbo.Clientage
     WHERE CDiscount = 0.5;

    -- Вывод таблицы только, если есть данные 
    DECLARE @count INT;
    SELECT @count = COUNT(*)
      FROM #TempTable;
    IF (@count > 0)
        SELECT *
          FROM #TempTable;
    ELSE
        SELECT 'Запрос 01: В таблице Clientage (Клиенты) нет данных для отображения';

    DROP TABLE #TempTable;
END;
GO

-- Выбирает из таблицы АГЕНТЫ, ДОГОВОРЫ, КЛИЕНТЫ информацию о страховых агентах и клиентах, 
-- заключивших договора о страховании автомобиля
CREATE PROCEDURE sp_Request02
AS
BEGIN
    SELECT DateConclusion,
           SumInsurance,
           [Type],
           Tariff,
           Clientage.CSecondName + ' ' + SUBSTRING(Clientage.CFirstName, 1, 1) + '. '
           + SUBSTRING(Clientage.CMiddleName, 1, 1) + '.' AS ClientNames,
           CPassport,
           CDiscount,
           Clientage.CPhoto,
           Agents.ASecondName + ' ' + SUBSTRING(Agents.AFirstName, 1, 1) + '. ' + SUBSTRING(Agents.AMiddleName, 1, 1)
           + '.' AS AgentNames,
           AReward,
           Agents.APhoto
      FROM dbo.Contracts
     INNER JOIN dbo.Clientage
        ON IdClient          = Clientage.Id
     INNER JOIN dbo.Agents
        ON IdAgent           = Agents.Id
     INNER JOIN dbo.TypesInsurance
        ON IdTypeInsurance   = TypesInsurance.Id
     WHERE IdTypeInsurance = 2;
END;
GO

-- Выбирает из таблиц КЛИЕНТЫ и ДОГОВОРЫ информацию о клиентах, заключивших договоры на 
-- сумму не меньше чем на 100 000 руб.
CREATE PROCEDURE sp_Request03
AS
BEGIN
    SELECT CSecondName,
           CFirstName,
           CMiddleName,
           CPassport,
           CDiscount,
           CPhoto,
           SumInsurance,
           DateConclusion
      FROM dbo.Contracts
     INNER JOIN dbo.Clientage
        ON IdClient          = Clientage.Id
     WHERE SumInsurance >= 100000;
END;
GO

-- Выбирает из таблицы КЛИЕНТЫ информацию о клиентах с заданной фамилией. 
-- Фамилия вводится при выполнении запроса (в разработанном приложении)
CREATE PROCEDURE sp_Request04 @secondName NVARCHAR(50)
AS
BEGIN
    SELECT *
      FROM dbo.Clientage
     WHERE CSecondName = @secondName;
END;
GO

-- Выбирает из таблиц КЛИЕНТЫ, ДОГОВОРЫ и АГЕНТЫ информацию обо всех договорах 
-- (ФИО клиента, Вид страхования, Сумма страхования, Дата заключения договора, ФИО агента), 
-- заключенных в некоторый заданный период времени о жилищном страховании. 
-- Нижняя и верхняя границы периода задаются при выполнении запроса (в разработанном приложении)
CREATE PROCEDURE sp_Request05
    @dateFrom DATE,
    @dateTo DATE
AS
BEGIN
    SELECT Clientage.CSecondName + ' ' + SUBSTRING(Clientage.CFirstName, 1, 1) + '. '
           + SUBSTRING(Clientage.CMiddleName, 1, 1) + '.' AS ClientNames,
           [Type],
           SumInsurance,
           DateConclusion,
           Agents.ASecondName + ' ' + SUBSTRING(Agents.AFirstName, 1, 1) + '. ' + SUBSTRING(Agents.AMiddleName, 1, 1)
           + '.' AS AgentNames
      FROM dbo.Contracts
     INNER JOIN dbo.Clientage
        ON IdClient        = Clientage.Id
     INNER JOIN dbo.Agents
        ON IdAgent         = Agents.Id
     INNER JOIN dbo.TypesInsurance
        ON IdTypeInsurance = TypesInsurance.Id
     WHERE IdTypeInsurance = 1
       AND DateConclusion BETWEEN @dateFrom AND @dateTo;
END;
GO

-- Вычисляет для каждого договора размер комиссионного вознаграждения агента. 
-- Включает поля 
-- Дата заключения договора, 
-- Фамилия агента, 
-- Имя агента, 
-- Отчество агента, 
-- Сумма страхования, 
-- Комиссионные. Сортировка по полю Дата заключения договора
-- SumInsurance * (Tariff - Discount) = страховая премия
-- TODO: в подсчёте комиссионных явно что-то не так...
CREATE PROCEDURE sp_Request06
AS
BEGIN
    SELECT DateConclusion,
           Agents.ASecondName,
           Agents.AFirstName,
           Agents.AMiddleName,
           SumInsurance, 
		   CONVERT(MONEY, STR(AReward * (SumInsurance * (Tariff - CDiscount)))) AS Commission
      FROM dbo.Contracts
     INNER JOIN dbo.Agents
        ON IdAgent         = Agents.Id
     INNER JOIN dbo.Clientage
        ON IdClient        = Clientage.Id
     INNER JOIN dbo.TypesInsurance
        ON IdTypeInsurance = TypesInsurance.Id
     ORDER BY DateConclusion;
END;
GO

-- Выполняет группировку по полю Код агента в таблице ДОГОВОРЫ. 
-- Для каждой группы вычисляет максимальное и минимальное значение суммы страхования
CREATE PROCEDURE sp_Request07
AS
BEGIN
    SELECT MAX(SumInsurance)   AS MaxSumInsurance,
           MIN(SumInsurance)   AS MinSumInsurance,
           COUNT(SumInsurance) AS CountSums
      FROM dbo.Contracts
     INNER JOIN dbo.Agents
        ON IdAgent = Agents.Id
     GROUP BY Agents.Id;
END;
GO

-- Выполняет группировку по полю Дата заключения договора для договоров страхования автомобиля. 
-- Для каждой группы вычисляет среднее значения по полю Сумма страхования
CREATE PROCEDURE sp_Request08
AS
BEGIN
    SELECT AVG(SumInsurance) AS AvgSumInsurance
      FROM dbo.Contracts
     WHERE IdTypeInsurance = 2
     GROUP BY DateConclusion;
END;
GO

-- Создает таблицу НОВЫЕ_КЛИЕНТЫ, содержащую информацию о клиентах, для которых процент скидки равен нулю
CREATE PROCEDURE sp_Request09
AS
BEGIN
	IF (OBJECT_ID('NewClients') IS NOT NULL)
	    DROP TABLE NewClients;

    SELECT *
    INTO   #TempTable
      FROM dbo.Clientage
     WHERE CDiscount = 0.0;

    DECLARE @count INT;
    SELECT @count = COUNT(*)
      FROM #TempTable;
    IF (@count > 0)
    BEGIN
        SELECT *
        INTO   NewClients
          FROM #TempTable;

        SELECT *
          FROM NewClients;
    END;
    ELSE
        SELECT 'Запрос 09: В таблице Clientage (Клиенты) нет данных для создания новой таблицы NewClients (Новые клиенты)';

    DROP TABLE #TempTable;
END;
GO

-- Создает копию таблицы КЛИЕНТЫ с именем КОПИЯ_КЛИЕНТЫ
CREATE PROCEDURE sp_Request10
AS
BEGIN
    SELECT *
    INTO   #TempTable
      FROM dbo.Clientage;

    DECLARE @count INT;
    SELECT @count = COUNT(*)
      FROM #TempTable;
    IF (@count > 0)
    BEGIN
        IF OBJECT_ID('CopyClientage') IS NULL
        BEGIN
            SELECT *
            INTO   CopyClientage
              FROM #TempTable;
            SELECT *
              FROM CopyClientage;
        END;
        ELSE
        BEGIN
            DROP TABLE CopyClientage;
            SELECT *
            INTO   CopyClientage
              FROM #TempTable;

            SELECT *
              FROM CopyClientage;
        END;
    END;
    ELSE
        SELECT 'Запрос 10: В таблице Clientage (Клиенты) нет данных для создания её копии';

    DROP TABLE #TempTable;
END;
GO

-- Удаляет из таблицы КОПИЯ_КЛИЕНТЫ записи, в которых значение в поле Процент скидки равен 0.5%
CREATE PROCEDURE sp_Request11
AS
BEGIN
    IF OBJECT_ID('CopyClientage') IS NULL
    BEGIN
        EXECUTE sp_Request10;
        PRINT ('Выполнен запрос №10 на создание копии таблицы клиентов.');
    END;

    DELETE FROM CopyClientage
     WHERE CDiscount = 0.5;

    SELECT *
    INTO   #TempTable
      FROM CopyClientage;

    DECLARE @count INT;
    SELECT @count = COUNT(*)
      FROM #TempTable;
    IF (@count > 0)
    BEGIN
        SELECT *
          FROM #TempTable;
    END;
    ELSE
        SELECT 'Запрос 11: В таблице CopyClientage нет нужных данных';

    DROP TABLE #TempTable;
END;
GO

-- Устанавливает значение в поле Процент скидки в таблице 
-- КОПИЯ_КЛИЕНТЫ равным 0.5% для клиентов, имеющих процент скидки 0.4%
CREATE PROCEDURE sp_Request12
AS
BEGIN
    IF OBJECT_ID('CopyClientage') IS NULL
    BEGIN
        SELECT *
        INTO   CopyClientage
          FROM dbo.Clientage;
        PRINT ('Создана копия таблицы Клиентуры (CopyClientage)');
    END;

    UPDATE CopyClientage
       SET CDiscount = 0.5
      FROM CopyClientage
     WHERE CDiscount = 0.4;

    SELECT *
      FROM CopyClientage;
END;
GO