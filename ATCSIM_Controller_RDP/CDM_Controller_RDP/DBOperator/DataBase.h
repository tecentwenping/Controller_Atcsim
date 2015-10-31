#include "DatabaseAccess.h"
#include "myReflect.h"
class DataBaseAccessObj
{
private:
	static CDM_OracleDatabaseAccess *m_pOracleDBConnection;
	static CDM_SQLDatabaseAccess    *m_pSQLDBConnection;
public:
	static CDM_OracleDatabaseAccess*	GetInstance();
	static CDM_SQLDatabaseAccess*		GetSQLAccessInstance();
};