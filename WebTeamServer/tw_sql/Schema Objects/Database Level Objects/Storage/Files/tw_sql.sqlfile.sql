﻿ALTER DATABASE [$(DatabaseName)]
    ADD FILE (NAME = [tw_sql], FILENAME = '$(DefaultDataPath)$(DatabaseName).mdf', FILEGROWTH = 1024 KB) TO FILEGROUP [PRIMARY];

