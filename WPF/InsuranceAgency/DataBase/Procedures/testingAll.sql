-- Script by: Alexey Bur'yanov, 27.06.2017

-- Тестирование уже созданных процедур

USE InsuranceContractsAB;
GO

-- request01
EXECUTE sp_Request01;

-- request02
EXECUTE sp_Request02;

-- request03
EXECUTE sp_Request03;

-- request04
EXECUTE sp_Request04 'Давыдова';

-- request05
EXECUTE sp_Request05 '01.01.2012', '28.06.2017';

-- request06
EXECUTE sp_Request06;

-- request07
EXECUTE sp_Request07;

-- request08
EXECUTE sp_Request08;

-- request09
EXECUTE sp_Request09;

-- request10
EXECUTE sp_Request10;

-- request11
EXECUTE sp_Request11;

-- request12
EXECUTE sp_Request12;