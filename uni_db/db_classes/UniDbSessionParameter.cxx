// ----------------------------------------------------------------------
//                    UniDbSessionParameter cxx file 
//                      Generated 20-10-2015 
// ----------------------------------------------------------------------

#include "TSQLServer.h"
#include "TSQLStatement.h"

#include "UniDbSessionParameter.h"

#include <iostream>
using namespace std;

/* GENERATED CLASS MEMBERS (SHOULDN'T BE CHANGED MANUALLY) */
// -----   Constructor with database connection   -----------------------
UniDbSessionParameter::UniDbSessionParameter(UniDbConnection* connUniDb, int session_number, TString detector_name, int parameter_id, unsigned char* parameter_value, Long_t size_parameter_value)
{
	connectionUniDb = connUniDb;

	i_session_number = session_number;
	str_detector_name = detector_name;
	i_parameter_id = parameter_id;
	blob_parameter_value = parameter_value;
	sz_parameter_value = size_parameter_value;
}

// -----   Destructor   -------------------------------------------------
UniDbSessionParameter::~UniDbSessionParameter()
{
	if (connectionUniDb)
		delete connectionUniDb;
	if (blob_parameter_value)
		delete [] blob_parameter_value;
}

// -----   Creating new record in class table ---------------------------
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, int parameter_id, unsigned char* parameter_value, Long_t size_parameter_value)
{
	UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
	if (connUniDb == 0x00) return 0x00;

	TSQLServer* uni_db = connUniDb->GetSQLServer();

	TString sql = TString::Format(
		"insert into session_parameter(session_number, detector_name, parameter_id, parameter_value) "
		"values ($1, $2, $3, $4)");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetInt(0, session_number);
	stmt->SetString(1, detector_name);
	stmt->SetInt(2, parameter_id);
	stmt->SetLargeObject(3, parameter_value, size_parameter_value, 0x4000000);

	// inserting new record to DB
	if (!stmt->Process())
	{
		cout<<"Error: inserting new record to DB has been failed"<<endl;
		delete stmt;
		delete connUniDb;
		return 0x00;
	}

	delete stmt;

	int tmp_session_number;
	tmp_session_number = session_number;
	TString tmp_detector_name;
	tmp_detector_name = detector_name;
	int tmp_parameter_id;
	tmp_parameter_id = parameter_id;
	unsigned char* tmp_parameter_value;
	Long_t tmp_sz_parameter_value = size_parameter_value;
	tmp_parameter_value = new unsigned char[tmp_sz_parameter_value];
	memcpy(tmp_parameter_value, parameter_value, tmp_sz_parameter_value);

	return new UniDbSessionParameter(connUniDb, tmp_session_number, tmp_detector_name, tmp_parameter_id, tmp_parameter_value, tmp_sz_parameter_value);
}

// -----   Get table record from database ---------------------------
UniDbSessionParameter* UniDbSessionParameter::GetSessionParameter(int session_number, TString detector_name, int parameter_id)
{
	UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
	if (connUniDb == 0x00) return 0x00;

	TSQLServer* uni_db = connUniDb->GetSQLServer();

	TString sql = TString::Format(
		"select session_number, detector_name, parameter_id, parameter_value "
		"from session_parameter "
		"where session_number = %d and lower(detector_name) = lower('%s') and parameter_id = %d", session_number, detector_name.Data(), parameter_id);
	TSQLStatement* stmt = uni_db->Statement(sql);

	// get table record from DB
	if (!stmt->Process())
	{
		cout<<"Error: getting record from DB has been failed"<<endl;

		delete stmt;
		delete connUniDb;
		return 0x00;
	}

	// store result of statement in buffer
	stmt->StoreResult();

	// extract row
	if (!stmt->NextResultRow())
	{
		cout<<"Error: table record wasn't found"<<endl;

		delete stmt;
		delete connUniDb;
		return 0x00;
	}

	int tmp_session_number;
	tmp_session_number = stmt->GetInt(0);
	TString tmp_detector_name;
	tmp_detector_name = stmt->GetString(1);
	int tmp_parameter_id;
	tmp_parameter_id = stmt->GetInt(2);
	unsigned char* tmp_parameter_value;
	tmp_parameter_value = NULL;
	Long_t tmp_sz_parameter_value = 0;
	stmt->GetLargeObject(3, (void*&)tmp_parameter_value, tmp_sz_parameter_value);

	delete stmt;

	return new UniDbSessionParameter(connUniDb, tmp_session_number, tmp_detector_name, tmp_parameter_id, tmp_parameter_value, tmp_sz_parameter_value);
}

// -----   Delete record from class table ---------------------------
int UniDbSessionParameter::DeleteSessionParameter(int session_number, TString detector_name, int parameter_id)
{
	UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
	if (connUniDb == 0x00) return 0x00;

	TSQLServer* uni_db = connUniDb->GetSQLServer();

	TString sql = TString::Format(
		"delete from session_parameter "
		"where session_number = $1 and lower(detector_name) = lower($2) and parameter_id = $3");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetInt(0, session_number);
	stmt->SetString(1, detector_name);
	stmt->SetInt(2, parameter_id);

	// delete table record from DB
	if (!stmt->Process())
	{
		cout<<"Error: deleting record from DB has been failed"<<endl;

		delete stmt;
		delete connUniDb;
		return -1;
	}

	delete stmt;
	delete connUniDb;
	return 0;
}

// -----   Print all table records ---------------------------------
int UniDbSessionParameter::PrintAll()
{
	UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
	if (connUniDb == 0x00) return 0x00;

	TSQLServer* uni_db = connUniDb->GetSQLServer();

	TString sql = TString::Format(
		"select session_number, detector_name, parameter_id, parameter_value "
		"from session_parameter");
	TSQLStatement* stmt = uni_db->Statement(sql);

	// get table record from DB
	if (!stmt->Process())
	{
		cout<<"Error: getting all records from DB has been failed"<<endl;

		delete stmt;
		delete connUniDb;
		return -1;
	}

	// store result of statement in buffer
	stmt->StoreResult();

	// print rows
	cout<<"Table 'session_parameter'"<<endl;
	while (stmt->NextResultRow())
	{
		cout<<". session_number: ";
		cout<<(stmt->GetInt(0));
		cout<<". detector_name: ";
		cout<<(stmt->GetString(1));
		cout<<". parameter_id: ";
		cout<<(stmt->GetInt(2));
		cout<<". parameter_value: ";
		unsigned char* tmp_parameter_value = NULL;
		Long_t tmp_sz_parameter_value=0;
		stmt->GetLargeObject(3, (void*&)tmp_parameter_value, tmp_sz_parameter_value);
		cout<<(void*)tmp_parameter_value<<", binary size: "<<tmp_sz_parameter_value;
		cout<<endl;
	}

	delete stmt;
	delete connUniDb;

	return 0;
}


// Setters functions
int UniDbSessionParameter::SetSessionNumber(int session_number)
{
	if (!connectionUniDb)
	{
		cout<<"Connection object is null"<<endl;
		return -1;
	}

	TSQLServer* uni_db = connectionUniDb->GetSQLServer();

	TString sql = TString::Format(
		"update session_parameter "
		"set session_number = $1 "
		"where session_number = $2 and detector_name = $3 and parameter_id = $4");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetInt(0, session_number);
	stmt->SetInt(1, i_session_number);
	stmt->SetString(2, str_detector_name);
	stmt->SetInt(3, i_parameter_id);

	// write new value to database
	if (!stmt->Process())
	{
		cout<<"Error: updating the record has been failed"<<endl;

		delete stmt;
		return -2;
	}

	i_session_number = session_number;

	delete stmt;
	return 0;
}

int UniDbSessionParameter::SetDetectorName(TString detector_name)
{
	if (!connectionUniDb)
	{
		cout<<"Connection object is null"<<endl;
		return -1;
	}

	TSQLServer* uni_db = connectionUniDb->GetSQLServer();

	TString sql = TString::Format(
		"update session_parameter "
		"set detector_name = $1 "
		"where session_number = $2 and detector_name = $3 and parameter_id = $4");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetString(0, detector_name);
	stmt->SetInt(1, i_session_number);
	stmt->SetString(2, str_detector_name);
	stmt->SetInt(3, i_parameter_id);

	// write new value to database
	if (!stmt->Process())
	{
		cout<<"Error: updating the record has been failed"<<endl;

		delete stmt;
		return -2;
	}

	str_detector_name = detector_name;

	delete stmt;
	return 0;
}

int UniDbSessionParameter::SetParameterId(int parameter_id)
{
	if (!connectionUniDb)
	{
		cout<<"Connection object is null"<<endl;
		return -1;
	}

	TSQLServer* uni_db = connectionUniDb->GetSQLServer();

	TString sql = TString::Format(
		"update session_parameter "
		"set parameter_id = $1 "
		"where session_number = $2 and detector_name = $3 and parameter_id = $4");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetInt(0, parameter_id);
	stmt->SetInt(1, i_session_number);
	stmt->SetString(2, str_detector_name);
	stmt->SetInt(3, i_parameter_id);

	// write new value to database
	if (!stmt->Process())
	{
		cout<<"Error: updating the record has been failed"<<endl;

		delete stmt;
		return -2;
	}

	i_parameter_id = parameter_id;

	delete stmt;
	return 0;
}

int UniDbSessionParameter::SetParameterValue(unsigned char* parameter_value, Long_t size_parameter_value)
{
	if (!connectionUniDb)
	{
		cout<<"Connection object is null"<<endl;
		return -1;
	}

	TSQLServer* uni_db = connectionUniDb->GetSQLServer();

	TString sql = TString::Format(
		"update session_parameter "
		"set parameter_value = $1 "
		"where session_number = $2 and detector_name = $3 and parameter_id = $4");
	TSQLStatement* stmt = uni_db->Statement(sql);

	stmt->NextIteration();
	stmt->SetLargeObject(0, parameter_value, size_parameter_value, 0x4000000);
	stmt->SetInt(1, i_session_number);
	stmt->SetString(2, str_detector_name);
	stmt->SetInt(3, i_parameter_id);

	// write new value to database
	if (!stmt->Process())
	{
		cout<<"Error: updating the record has been failed"<<endl;

		delete stmt;
		return -2;
	}

	if (blob_parameter_value)
		delete [] blob_parameter_value;
	sz_parameter_value = size_parameter_value;
	blob_parameter_value = new unsigned char[sz_parameter_value];
	memcpy(blob_parameter_value, parameter_value, sz_parameter_value);

	delete stmt;
	return 0;
}

// -----   Print current record ---------------------------------------
void UniDbSessionParameter::Print()
{
	cout<<"Table 'session_parameter'";
	cout<<". session_number: "<<i_session_number<<". detector_name: "<<str_detector_name<<". parameter_id: "<<i_parameter_id<<". parameter_value: "<<(void*)blob_parameter_value<<", binary size: "<<sz_parameter_value<<endl;

	return;
}
/* END OF GENERATED CLASS PART (SHOULDN'T BE CHANGED MANUALLY) */

// get detector parameter by session number, detector name and parameter name
UniDbSessionParameter* UniDbSessionParameter::GetSessionParameter(int session_number, TString detector_name, TString parameter_name)
{
    UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
    if (connUniDb == 0x00) return 0x00;

    TSQLServer* uni_db = connUniDb->GetSQLServer();

    TString sql = TString::Format(
        "select session_number, detector_name, p.parameter_id, parameter_value "
        "from session_parameter dp join parameter_ p on dp.parameter_id = p.parameter_id "
        "where session_number = %d and lower(detector_name) = lower('%s') and lower(parameter_name) = lower('%s')", session_number, detector_name.Data(), parameter_name.Data());
    TSQLStatement* stmt = uni_db->Statement(sql);

    // get table record from DB
    if (!stmt->Process())
    {
        cout<<"Error: getting record from DB has been failed"<<endl;

        delete stmt;
        delete connUniDb;
        return 0x00;
    }

    // store result of statement in buffer
    stmt->StoreResult();

    // extract row
    if (!stmt->NextResultRow())
    {
        cout<<"Error: table record wasn't found"<<endl;

        delete stmt;
        delete connUniDb;
        return 0x00;
    }

    int tmp_session_number;
    tmp_session_number = stmt->GetInt(0);
    TString tmp_detector_name;
    tmp_detector_name = stmt->GetString(1);
    int tmp_parameter_id;
    tmp_parameter_id = stmt->GetInt(2);
    unsigned char* tmp_parameter_value = NULL;
    Long_t tmp_sz_parameter_value = 0;
    stmt->GetLargeObject(3, (void*&)tmp_parameter_value, tmp_sz_parameter_value);

    delete stmt;

    return new UniDbSessionParameter(connUniDb, tmp_session_number, tmp_detector_name, tmp_parameter_id, tmp_parameter_value, tmp_sz_parameter_value);
}

// common function for creating parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, unsigned char* p_parameter_value, Long_t size_parameter_value, enumParameterType enum_parameter_type)
{
    UniDbConnection* connUniDb = UniDbConnection::Open(UNIFIED_DB);
    if (connUniDb == 0x00) return 0x00;

    TSQLServer* uni_db = connUniDb->GetSQLServer();

    int parameter_id = -1;
    bool res_code = UniDbParameter::CheckAndGetParameterID(uni_db, parameter_name, enum_parameter_type, parameter_id);
    if (!res_code)
    {
        delete connUniDb;
        return 0x00;
    }

    TString sql = TString::Format(
        "insert into session_parameter(session_number, detector_name, parameter_id, parameter_value) "
        "values ($1, $2, $3, $4)");
    TSQLStatement* stmt = uni_db->Statement(sql);

    stmt->NextIteration();
    stmt->SetInt(0, session_number);
    stmt->SetString(1, detector_name);
    stmt->SetInt(2, parameter_id);
    stmt->SetLargeObject(3, (void*)p_parameter_value, size_parameter_value);
    //cout<<p_parameter_value<<" "<<p_parameter_value[0]<<" "<<size_parameter_value<<endl;

    // inserting new record to DB
    if (!stmt->Process())
    {
        cout<<"Error: inserting new parameter value to DB has been failed"<<endl;
        delete stmt;
        delete connUniDb;
        return 0x00;
    }

    delete stmt;

    return new UniDbSessionParameter(connUniDb, session_number, detector_name, parameter_id, p_parameter_value, size_parameter_value);
}

// create boolean detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, bool parameter_value)
{
    Long_t size_parameter_value = sizeof(bool);
    bool* p_parameter_value = new bool[1];
    p_parameter_value[0] = parameter_value;

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, (unsigned char*) p_parameter_value, size_parameter_value, BoolType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create integer detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, int parameter_value)
{
    Long_t size_parameter_value = sizeof(Int_t);
    Int_t* p_parameter_value = new Int_t[1];
    p_parameter_value[0] = parameter_value;

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, (unsigned char*) p_parameter_value, size_parameter_value, IntType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create double detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, double parameter_value)
{
    Long_t size_parameter_value = sizeof(Double_t);
    Double_t* p_parameter_value = new Double_t[1];
    p_parameter_value[0] = parameter_value;

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, (unsigned char*) p_parameter_value, size_parameter_value, DoubleType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create string detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, TString parameter_value)
{
    Long_t size_parameter_value = parameter_value.Length()+1;
    char* p_parameter_value = new char[size_parameter_value];
    strcpy(p_parameter_value, parameter_value.Data());

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, (unsigned char*) p_parameter_value, size_parameter_value, StringType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create Integer Array detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, int* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(int);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, p_parameter_value, size_parameter_value, IntArrayType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create Double Array detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, double* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(double);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, p_parameter_value, size_parameter_value, DoubleArrayType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// create Int+Int Array detector parameter
UniDbSessionParameter* UniDbSessionParameter::CreateSessionParameter(int session_number, TString detector_name, TString parameter_name, IIStructure* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(IIStructure);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    UniDbSessionParameter* pSessionParameter = UniDbSessionParameter::CreateSessionParameter(session_number, detector_name, parameter_name, p_parameter_value, size_parameter_value, IIArrayType);

    if (pSessionParameter == 0x00)
        delete [] p_parameter_value;

    return pSessionParameter;
}

// common function for getting parameter
unsigned char* UniDbSessionParameter::GetUNC(enumParameterType enum_parameter_type)
{
    if (!connectionUniDb)
    {
        cout<<"Critical Error: Connection object is null"<<endl;
        return NULL;
    }

    TSQLServer* uni_db = connectionUniDb->GetSQLServer();

    // get parameter object from 'parameter_' table
    TString sql = TString::Format(
        "select parameter_name, parameter_type "
        "from parameter_ "
        "where parameter_id = %d", i_parameter_id);
    TSQLStatement* stmt = uni_db->Statement(sql);

    // get table record from DB
    if (!stmt->Process())
    {
        cout<<"Critical Error: getting record with parameter from 'parameter_' table has been failed"<<endl;
        delete stmt;
        return NULL;
    }

    stmt->StoreResult();

    // extract row with parameter
    if (!stmt->NextResultRow())
    {
        cout<<"Critical Error: the parameter with id '"<<i_parameter_id<<"' wasn't found"<<endl;
        delete stmt;
        return NULL;
    }

    TString parameter_name = stmt->GetString(0);
    int parameter_type = stmt->GetInt(1);
    delete stmt;

    if (parameter_type != enum_parameter_type)
    {
        cout<<"Critical Error: the parameter with name '"<<parameter_name<<"' isn't as getting type"<<endl;
        return NULL;
    }

    return blob_parameter_value;
}

// get boolean value of detector parameter (for current session, detector and parameter)
bool UniDbSessionParameter::GetBool()
{
    return *((bool*) GetUNC(BoolType));
}

// get integer value of detector parameter (for current session, detector and parameter)
int UniDbSessionParameter::GetInt()
{
    return *((int*) GetUNC(IntType));
}

// get double value of detector parameter (for current session, detector and parameter)
double UniDbSessionParameter::GetDouble()
{
    return *((double*) GetUNC(DoubleType));
}

// get string value of detector parameter (for current session, detector and parameter)
TString UniDbSessionParameter::GetString()
{
    return (char*) GetUNC(StringType);
}

// get Integer array for detector parameter (for current session, detector and parameter)
int UniDbSessionParameter::GetIntArray(int*& parameter_value, int& element_count)
{
    unsigned char* p_parameter_value = GetUNC(IntArrayType);
    if (p_parameter_value == NULL)
        return - 1;

    element_count = sz_parameter_value / sizeof(int);
    parameter_value = new int[element_count];
    memcpy(parameter_value, p_parameter_value, sz_parameter_value);

    return 0;
}

// get Double array for detector parameter (for current session, detector and parameter)
int UniDbSessionParameter::GetDoubleArray(double*& parameter_value, int& element_count)
{
    unsigned char* p_parameter_value = GetUNC(DoubleArrayType);
    if (p_parameter_value == NULL)
        return - 1;

    element_count = sz_parameter_value / sizeof(double);
    parameter_value = new double[element_count];
    memcpy(parameter_value, p_parameter_value, sz_parameter_value);

    return 0;
}

// get Int+Int array for detector parameter (for current session, detector and parameter)
int UniDbSessionParameter::GetIIArray(IIStructure*& parameter_value, int& element_count)
{
    unsigned char* p_parameter_value = GetUNC(IIArrayType);
    if (p_parameter_value == NULL)
        return - 1;

    element_count = sz_parameter_value / sizeof(IIStructure);
    parameter_value = new IIStructure[element_count];
    memcpy(parameter_value, p_parameter_value, sz_parameter_value);

    return 0;
}

// common function for setting parameter
int UniDbSessionParameter::SetUNC(unsigned char* p_parameter_value, Long_t size_parameter_value)
{
    if (!connectionUniDb)
    {
        cout<<"Connection object is null"<<endl;
        return -1;
    }

    TSQLServer* uni_db = connectionUniDb->GetSQLServer();

    TString sql = TString::Format(
        "update session_parameter "
        "set parameter_value = $1 "
        "where session_number = $2 and detector_name = $3 and parameter_id = $4");
    TSQLStatement* stmt = uni_db->Statement(sql);

    stmt->NextIteration();
    stmt->SetLargeObject(0, (void*)p_parameter_value, size_parameter_value);
    stmt->SetInt(1, i_session_number);
    stmt->SetString(2, str_detector_name);
    stmt->SetInt(3, i_parameter_id);

    // write new value to database
    if (!stmt->Process())
    {
        cout<<"Error: updating the detector parameter has been failed"<<endl;
        delete stmt;
        return -2;
    }

    if (blob_parameter_value) delete [] blob_parameter_value;
    blob_parameter_value = p_parameter_value;
    sz_parameter_value = size_parameter_value;

    delete stmt;
    return 0;
}

// set boolean value to detector parameter
int UniDbSessionParameter::SetBool(bool parameter_value)
{
    Long_t size_parameter_value = sizeof(bool);
    bool* p_parameter_value = new bool[1];
    p_parameter_value[0] = parameter_value;

    int res_code = SetUNC((unsigned char*)p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set integer value to detector parameter
int UniDbSessionParameter::SetInt(int parameter_value)
{
    Long_t size_parameter_value = sizeof(Int_t);
    Int_t* p_parameter_value = new Int_t[1];
    p_parameter_value[0] = parameter_value;

    int res_code = SetUNC((unsigned char*)p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set double value to detector parameter
int UniDbSessionParameter::SetDouble(double parameter_value)
{
    Long_t size_parameter_value = sizeof(Double_t);
    Double_t* p_parameter_value = new Double_t[1];
    p_parameter_value[0] = parameter_value;

    int res_code = SetUNC((unsigned char*)p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set string value to detector parameter
int UniDbSessionParameter::SetString(TString parameter_value)
{
    Long_t size_parameter_value = parameter_value.Length()+1;
    char* p_parameter_value = new char[size_parameter_value];
    strcpy(p_parameter_value, parameter_value.Data());

    int res_code = SetUNC((unsigned char*)p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set Integer array for detector parameter
int UniDbSessionParameter::SetIntArray(int* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(int);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    int res_code = SetUNC(p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set Double array for detector parameter
int UniDbSessionParameter::SetDoubleArray(double* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(double);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    int res_code = SetUNC(p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// set Int+Int array for detector parameter
int UniDbSessionParameter::SetIIArray(IIStructure* parameter_value, int element_count)
{
    Long_t size_parameter_value = element_count * sizeof(IIStructure);
    unsigned char* p_parameter_value = new unsigned char[size_parameter_value];
    memcpy(p_parameter_value, parameter_value, size_parameter_value);

    int res_code = SetUNC(p_parameter_value, size_parameter_value);
    if (res_code != 0)
    {
        delete [] p_parameter_value;
        return res_code;
    }

    return 0;
}

// -------------------------------------------------------------------
ClassImp(UniDbSessionParameter);