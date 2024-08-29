#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Ativo {
    string ticket;
    int quantidade;
    double preco_medio;

    Ativo(string t, int q, double p) : ticket(t), quantidade(q), preco_medio(p) {}
};

class Carteira {
private:
    vector<Ativo> ativos;

    int busca_binaria(int esq, int dir, const string& ticket) {
        if (dir >= esq) {
            int meio = esq + (dir - esq) / 2;

            if (ativos[meio].ticket == ticket)
                return meio;

            if (ativos[meio].ticket > ticket)
                return busca_binaria(esq, meio - 1, ticket);

            return busca_binaria(meio + 1, dir, ticket);
        }

        return -1;
    }

public:
    void registrar_compra() {
        string ticket;
        int quantidade;
        double valor;

        cout << "Ticket do ativo (ex: ITSA4, BBAS3): ";
        cin >> ticket;
        cout << "Quantidade comprada: ";
        cin >> quantidade;
        cout << "Valor do ativo no momento da compra: ";
        cin >> valor;

        int idx = busca_binaria(0, ativos.size() - 1, ticket);

        if (idx == -1) {
            ativos.push_back(Ativo(ticket, quantidade, valor));
            sort(ativos.begin(), ativos.end(), [](Ativo a, Ativo b) { return a.ticket < b.ticket; });
        } else {
            Ativo& ativo = ativos[idx];
            ativo.preco_medio = ((ativo.preco_medio * ativo.quantidade) + (valor * quantidade)) / (ativo.quantidade + quantidade);
            ativo.quantidade += quantidade;
        }

        cout << "Compra registrada com sucesso!\n";
    }

    void registrar_venda() {
        string ticket;
        int quantidade;
        double valor;

        cout << "Ticket do ativo (ex: ITSA4, BBAS3): ";
        cin >> ticket;
        cout << "Quantidade vendida: ";
        cin >> quantidade;
        cout << "Valor do ativo no momento da venda: ";
        cin >> valor;

        int idx = busca_binaria(0, ativos.size() - 1, ticket);

        if (idx == -1) {
            cout << "Ativo não encontrado!\n";
            return;
        }

        Ativo& ativo = ativos[idx];

        if (ativo.quantidade < quantidade) {
            cout << "Quantidade insuficiente para venda!\n";
            return;
        }

        ativo.quantidade -= quantidade;
        if (ativo.quantidade == 0) {
            ativos.erase(ativos.begin() + idx);
        }

        cout << "Venda registrada com sucesso!\n";
    }

    void ver_saldo_ativo() {
        string ticket;
        cout << "Ticket do ativo (ex: ITSA4, BBAS3): ";
        cin >> ticket;

        int idx = busca_binaria(0, ativos.size() - 1, ticket);

        if (idx == -1) {
            cout << "Ativo não encontrado!\n";
            return;
        }

        Ativo& ativo = ativos[idx];
        cout << "Saldo do ativo " << ativo.ticket << ": " << ativo.quantidade << " ações, Preço médio: R$ " << ativo.preco_medio << "\n";
    }

    void listar_patrimonio() {
        if (ativos.empty()) {
            cout << "Nenhum ativo na carteira.\n";
            return;
        }

        cout << "Patrimônio:\n";
        for (const auto& ativo : ativos) {
            cout << ativo.ticket << ": " << ativo.quantidade << " ações, Preço médio: R$ " << ativo.preco_medio << "\n";
        }
    }
};

void exibir_menu() {
    cout << "Menu:\n";
    cout << "1. Registrar compra\n";
    cout << "2. Registrar venda\n";
    cout << "3. Ver saldo de um ativo\n";
    cout << "4. Listar patrimônio\n";
    cout << "5. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    Carteira carteira;
    int opcao;

    do {
        exibir_menu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                carteira.registrar_compra();
                break;
            case 2:
                carteira.registrar_venda();
                break;
            case 3:
                carteira.ver_saldo_ativo();
                break;
            case 4:
                carteira.listar_patrimonio();
                break;
            case 5:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida! Tente novamente.\n";
        }

        cout << endl;
    } while (opcao != 5);

    return 0;
}
