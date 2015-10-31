#include "DataBase.h"
CDM_OracleDatabaseAccess* DataBaseAccessObj::m_pOracleDBConnection=static_cast<CDM_OracleDatabaseAccess*>(CDM_classFactory::CreateDatabaseInstance("CDM_OracleDatabaseAccess")); 
CDM_SQLDatabaseAccess * DataBaseAccessObj::m_pSQLDBConnection = static_cast<CDM_SQLDatabaseAccess*> (CDM_classFactory::CreateDatabaseInstance("CDM_SQLDatabaseAccess"));
CDM_OracleDatabaseAccess* DataBaseAccessObj::GetInstance()
{
	return m_pOracleDBConnection;
}

CDM_SQLDatabaseAccess* DataBaseAccessObj::GetSQLAccessInstance()
{
   return m_pSQLDBConnection;
}
