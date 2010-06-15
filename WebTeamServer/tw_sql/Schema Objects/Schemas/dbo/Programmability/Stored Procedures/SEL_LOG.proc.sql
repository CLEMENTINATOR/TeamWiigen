-- =============================================
-- Author:		Julien Morelle
-- Create date: 10/06/10
-- Description:	Get a lit of logs
-- =============================================
CREATE PROCEDURE [dbo].[SEL_LOG]
	@LOG_LTY_ID as int = null,
	@LOG_APV_ID as int = null,
	@LOG_START_DATE as date = null,
	@LOG_END_DATE as date = null,
	@APP_ID as int = null,
	@LOG_USER_IP as varchar(15) = null
AS
BEGIN
	SET NOCOUNT ON;
	SELECT	LOG_ID,
			LTY_VALUE,
			APP_NAME,
			APV_VALUE,
			LOG_MESSAGE,
			LOG_SOURCE,
			LOG_LINE,
			LOG_CREATION_DATE,
			LOG_USER_IP
		FROM	APPLICATION_VERSION INNER JOIN
                APPLICATIONS ON APV_APP_ID = APP_ID INNER JOIN
                LOG ON APV_ID = LOG_APV_ID INNER JOIN
                LOG_TYPE ON LOG_LTY_ID = LTY_ID
		WHERE	ISNULL(@LOG_LTY_ID, LOG_LTY_ID) = LOG_LTY_ID
			AND ISNULL(@LOG_APV_ID, LOG_APV_ID) = LOG_APV_ID
			AND ISNULL(@LOG_START_DATE, LOG_CREATION_DATE) = cast(LOG_CREATION_DATE as date)
			AND ISNULL(@LOG_END_DATE, LOG_CREATION_DATE) <= cast(LOG_CREATION_DATE as date)
			AND ISNULL(@APP_ID, APV_APP_ID) = APV_APP_ID
			AND ISNULL(@LOG_USER_IP, LOG_USER_IP) = LOG_USER_IP
    
END
