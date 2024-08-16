#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//Pour avoir les entrées des utilisateur
void parse_query_string(const string& query_string, string& username, string& password)
    {
        string key, value;
        stringstream ss(query_string);
        while (getline(ss, key, '=') && getline(ss, value, '&')) 
        {
            if (key == "username") 
            {
                username = value;
            } else if (key == "password") 
            {
                password = value;
            }
        }
}

//Pour verifier les entrées
bool verification(const string& username, const string& password) 
{
    ifstream file("/var/www/html/login/data.txt");
    string line, usernameAdmin, passwordAdmin;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        getline(ss, usernameAdmin, ' ');
        getline(ss, passwordAdmin, ' ');
        if (username == usernameAdmin && password == passwordAdmin) 
        {
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Content-Type: text/html\n\n";

    // Lire les données du formulaire
    string query_string;
    string username, password;
    getline(cin, query_string);

    parse_query_string(query_string, username, password);

    // Vérifier les informations d'identification
    bool valid = verification(username, password);

    cout << "<html><body>\n";
    // Si c'est valide
    if (valid) 
    {
        cout << "<h1>Connexion reussie</h1>\n";
        cout << "<p><strong>Nom d'utilisateur:</strong> " << username << "</p>\n";
        cout << "<p><strong>Mot de passe:</strong> " << password << "</p>\n";
    } 
    else 
    {
        cout << "<h1>Formulaire CGI</h1>\n";
        cout << "<form action=\"/cgi-bin/traitement.cgi\" method=\"post\">\n";
        cout << "<label for=\"username\">Nom:</label>\n";
        cout << "<input type=\"text\" id=\"username\" name=\"username\" value=\"" << username << "\" required><br><br>\n";
        cout << "<label for=\"password\">Mot de passe:</label>\n";
        cout << "<input type=\"password\" id=\"password\" name=\"password\" value=\"" << password << "\" required><br><br>\n";
        cout << "<input type=\"submit\" value=\"Envoyer\">\n";
        cout << "</form>\n";
    }
    cout << "</body></html>\n";

    return 0;
}
