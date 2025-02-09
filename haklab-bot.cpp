#include "include/chat-bot.hpp"
#include "include/systemtermux.hpp"

int main() {
    Chatbot bot;
    // Cargar la base de conocimiento desde el archivo JSON
    map<string, string> knowledgeBase = bot.loadKnowledgeBase("./haklab-base.json");

    cout << "Chatbot de I-HAKLAB" << endl;
    cout << "Escribe 'adios' para salir." << endl;

    string userInput;
    while (true) {
        cout << "\nTú: ";
        getline(cin, userInput);

        if (bot.toLower(userInput) == "adios") {
            cout << "Chatbot: " << bot.getResponse(userInput, knowledgeBase) << endl;
            break;
        }

        cout << "Chatbot: " << bot.getResponse(userInput, knowledgeBase) << endl;
    }

    // Guardar la base de conocimiento actualizada en el archivo JSON
    bot.saveKnowledgeBase("./haklab-base.json", knowledgeBase);
    
    return 0;
}
