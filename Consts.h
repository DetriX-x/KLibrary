#ifndef CONSTS_H
#define CONSTS_H

enum Page{
    Authorization, Registration, Client, Admin
};

enum RequestType{
    AuthorizationFailed, AuthorizationClient,
    AuthorizationAdmin, RegistrationFailed,
    RegistrationDone, QueryError, Exit
};

#endif // CONSTS_H
