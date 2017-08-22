-- Script by: Alexey Bur'yanov, 27.06.2017
-- Создание логического устройства и запись резервной копии

EXECUTE sp_addumpdevice 'disk', 'InsuranceContractsAB_backup', 'D:\InsuranceContractsAB.bak';
BACKUP DATABASE InsuranceContractsAB TO InsuranceContractsAB_backup;
GO