// Macro for printing TANGO data for GEM high voltage

// for datetime range
void tango_gem_u(char* date_start = "2016-12-21 12:20:00", char* date_end = "2016-12-21 12:40:00")
{
    gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
    basiclibs();
    gSystem->Load("libUniDb");

    UniDbTangoData db_tango;

    const char* detector_name = "gem";
    const char* parameter_name = "u";

    // TObjArray stores array of TangoTimeParameter* (parameter's values) for all time points (uni_db/UniDbTangoData.h)
    // tango_data->At(0) -> TangoTimeParameter*: parameter's values for fist time point of the given period (date_start - date_end)
    TObjArray* tango_data = db_tango.GetTangoParameter(detector_name, parameter_name, date_start, date_end);
    if (tango_data == NULL)
    {
        cout<<"Macro finished with errors"<<endl;
        exit(-1);
    }

    // console output
    db_tango.PrintTangoDataConsole(tango_data);

    // graph output
    //db_tango.PrintTangoDataSurface(tango_data);
    db_tango.PrintTangoDataMulti3D(tango_data);

    delete tango_data;

    cout<<"Macro finished successfully"<<endl;
}

// for a given run
void tango_gem_u(int period, int run)
{
    gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
    basiclibs();
    gSystem->Load("libUniDb");

    UniDbTangoData db_tango;

    // get run time
    UniDbRun* pRun = UniDbRun::GetRun(period, run);
    if (pRun == NULL)
    {
        cout<<"Macro finished with errors: no experimental run was found for given numbers"<<endl;
        exit(-2);
    }

    TString strDateStart = pRun->GetStartDatetime().AsSQLString();
    TDatime* dateEnd = pRun->GetEndDatetime();
    if (dateEnd == NULL)
    {
        cout<<"Macro finished with errors: no end datetime in the database for this run"<<endl;
        delete pRun;
        exit(-3);
    }
    TString strDateEnd = dateEnd->AsSQLString();
    delete pRun;

    const char* detector_name = "gem";
    const char* parameter_name = "u";

    // TObjArray stores array of TangoTimeParameter* (parameter's values) for all time points (uni_db/UniDbTangoData.h)
    // tango_data->At(0) -> TangoTimeParameter*: parameter's values for fist time point of the given period (date_start - date_end)
    TObjArray* tango_data = db_tango.GetTangoParameter(detector_name, parameter_name, strDateStart.Data(), strDateEnd.Data());
    if (tango_data == NULL)
    {
        cout<<"Macro finished with errors"<<endl;
        exit(-1);
    }

    // console output
    db_tango.PrintTangoDataConsole(tango_data);

    // graph output
    //db_tango.PrintTangoDataSurface(tango_data);
    db_tango.PrintTangoDataMulti3D(tango_data);

    delete tango_data;

    cout<<"Macro finished successfully"<<endl;
}
