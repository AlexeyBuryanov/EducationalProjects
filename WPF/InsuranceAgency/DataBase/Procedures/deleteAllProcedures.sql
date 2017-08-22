-- Script by: Alexey Bur'yanov, 27.06.2017

-- Удаление всех процедур, если они были созданы

USE InsuranceContractsAB;
GO

IF OBJECT_ID('sp_Request01') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request01;
	PRINT('Удаление процедуры sp_Request01: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request01: процедура не существует!');

IF OBJECT_ID('sp_Request02') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request02;
	PRINT('Удаление процедуры sp_Request02: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request02: процедура не существует!');

IF OBJECT_ID('sp_Request03') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request03;
	PRINT('Удаление процедуры sp_Request03: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request03: процедура не существует!');

IF OBJECT_ID('sp_Request04') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request04;
	PRINT('Удаление процедуры sp_Request04: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request04: процедура не существует!');

IF OBJECT_ID('sp_Request05') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request05;
	PRINT('Удаление процедуры sp_Request05: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request05: процедура не существует!');

IF OBJECT_ID('sp_Request06') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request06;
	PRINT('Удаление процедуры sp_Request06: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request06: процедура не существует!');

IF OBJECT_ID('sp_Request07') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request07;
	PRINT('Удаление процедуры sp_Request07: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request07: процедура не существует!');

IF OBJECT_ID('sp_Request08') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request08;
	PRINT('Удаление процедуры sp_Request08: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request08: процедура не существует!');

IF OBJECT_ID('sp_Request09') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request09;
	PRINT('Удаление процедуры sp_Request09: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request09: процедура не существует!');

IF OBJECT_ID('sp_Request10') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request10;
	PRINT('Удаление процедуры sp_Request10: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request10: процедура не существует!');

IF OBJECT_ID('sp_Request11') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request11;
	PRINT('Удаление процедуры sp_Request11: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request11: процедура не существует!');

IF OBJECT_ID('sp_Request12') IS NOT NULL
BEGIN
	DROP PROCEDURE sp_Request12;
	PRINT('Удаление процедуры sp_Request12: успешно.');
END ELSE PRINT('Удаление процедуры sp_Request12: процедура не существует!');
GO