﻿ALTER TABLE [dbo].[LOG]
    ADD CONSTRAINT [PK_LOGS] PRIMARY KEY CLUSTERED ([LOG_ID] ASC) WITH (ALLOW_PAGE_LOCKS = ON, ALLOW_ROW_LOCKS = ON, PAD_INDEX = OFF, IGNORE_DUP_KEY = OFF, STATISTICS_NORECOMPUTE = OFF);

