-- =============================================
-- Script Template
-- =============================================
IF NOT EXISTS(SELECT TOP(1) 1 FROM LOG_TYPE)
BEGIN
INSERT INTO LOG_TYPE(LTY_CODE, LTY_VALUE) VALUES('ERR', 'error')
INSERT INTO LOG_TYPE(LTY_CODE, LTY_VALUE) VALUES('WAR', 'warning')
INSERT INTO LOG_TYPE(LTY_CODE, LTY_VALUE) VALUES('NFO', 'info')
END