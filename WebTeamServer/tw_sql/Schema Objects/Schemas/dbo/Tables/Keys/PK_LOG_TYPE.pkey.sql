﻿ALTER TABLE [dbo].[LOG_TYPE]
    ADD CONSTRAINT [PK_LOG_TYPE] PRIMARY KEY CLUSTERED ([LTY_ID] ASC) WITH (ALLOW_PAGE_LOCKS = ON, ALLOW_ROW_LOCKS = ON, PAD_INDEX = OFF, IGNORE_DUP_KEY = OFF, STATISTICS_NORECOMPUTE = OFF);

