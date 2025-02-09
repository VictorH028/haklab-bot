#ifndef CHAT_BOT
#define CHAT_BOT

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


class Chatbot {
    std::ifstream file;
    public: 
    /**
     * @brief Convertir cadena a minuscula.
     * @pram str cadena a convertir   
     * @return string cana en minuscula  
     */ 
    string toLower(string str);
    /**
     *
     */
    map<string, string> loadKnowledgeBase(const string& filename); 
    /**
     *
     */
    void saveKnowledgeBase(const string& filename, const map<string, string>& knowledgeBase);
    /**
     *
     */
    string getResponse(const string& userInput, map<string, string>& knowledgeBase); 
};

string Chatbot::toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
};

map<string, string> Chatbot::loadKnowledgeBase(const string& filename) {
    map<string, string> knowledgeBase;

    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo JSON." << endl;
        return knowledgeBase;
    }

    json data;
    file >> data;

    for (const auto& item : data["preguntas"]) {
        string pregunta = toLower(item["pregunta"]);
        string respuesta = item["respuesta"];
        knowledgeBase[pregunta] = respuesta;
    }

    return knowledgeBase;
}

// Función para guardar la base de conocimiento en un archivo JSON
void Chatbot::saveKnowledgeBase(const string& filename, const map<string, string>& knowledgeBase) {
    json data;
    data["preguntas"] = json::array();

    for (const auto& pair : knowledgeBase) {
        json item;
        item["pregunta"] = pair.first;
        item["respuesta"] = pair.second;
        data["preguntas"].push_back(item);
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo JSON para guardar." << endl;
        return;
    }

    file << data.dump(4); // Guarda el JSON con indentación de 4 espacios
}

// Función para obtener una respuesta del chatbot
string Chatbot::getResponse(const string& userInput, map<string, string>& knowledgeBase) {
    string input = toLower(userInput);

    // Buscar la pregunta en la base de conocimiento
    for (const auto& pair : knowledgeBase) {
        if (input.find(pair.first) != string::npos) {
            return pair.second;
        }
    }

    // Si no se encuentra una coincidencia, pedir al usuario que enseñe al chatbot
    cout << "\nChatbot: No sé la respuesta a eso. ¿Puedes enseñarme? (Escribe la respuesta o 'skip' para omitir): ";
    string nuevaRespuesta;
    getline(cin, nuevaRespuesta);

    if (toLower(nuevaRespuesta) != "skip") {
        knowledgeBase[input] = nuevaRespuesta;
        cout << "Chatbot: ¡Gracias! He aprendido algo nuevo." << endl;
    }

    return "Lo siento, no sé la respuesta a eso todavía.";
}



#endif // !CHAT_BOT
#define CHAT_BOT
