import random

def gerar_vocabulário_ingles():
    # Lista de palavras e traduções em inglês e português
    palavras_ingles = [
        ("Bus", ["ônibus", "barramento"]),
        ("Bug", ["inseto", "problema"]),
        ("Bike", ["bicicleta"]),
        ("Coller", ["ventilador"]),
        ("Network", ["rede de computadores", "rede de relacionamento"]),
        ("System", ["sistema"]),
        ("Bicycle", ["bicicleta"]),
        ("Fan", ["ventilador"]),
        ("Computer", ["computador"]),
        ("Keyboard", ["teclado"]),
        ("Mouse", ["mouse", "rato"]),
        ("Screen", ["tela", "monitor"]),
        ("Printer", ["impressora"]),
        ("Table", ["mesa"]),
        ("Chair", ["cadeira"]),
        ("Window", ["janela"]),
        ("Door", ["porta"]),
        ("Book", ["livro"]),
        ("Pen", ["caneta"]),
        ("Pencil", ["lápis"]),
        ("Teacher", ["professor", "instrutor"]),
        ("Student", ["aluno", "estudante"]),
        ("Lesson", ["aula", "lição"]),
        ("Homework", ["lição de casa", "tarefa"]),
        ("Library", ["biblioteca"]),
        ("School", ["escola"]),
        ("Hospital", ["hospital"]),
        ("Doctor", ["médico", "doutor"]),
        ("Nurse", ["enfermeira", "enfermeiro"]),
        ("Pharmacy", ["farmácia"]),
        ("Market", ["mercado"]),
        ("Store", ["loja"]),
        ("Mall", ["shopping", "centro comercial"]),
        ("Bank", ["banco"]),
        ("Money", ["dinheiro"]),
        ("Card", ["cartão"]),
        ("House", ["casa"]),
        ("Apartment", ["apartamento"]),
        ("Building", ["prédio", "edifício"]),
        ("Garden", ["jardim"]),
        ("Park", ["parque"]),
        ("Street", ["rua"]),
        ("Avenue", ["avenida"]),
        ("Road", ["estrada", "caminho"]),
        ("Traffic", ["trânsito"]),
        ("Police", ["polícia"]),
        ("Firefighter", ["bombeiro"]),
        ("Ambulance", ["ambulância"]),
        ("Car", ["carro"]),
        ("Bike", ["bicicleta"]),
        ("Motorcycle", ["moto", "motocicleta"]),
        ("Airplane", ["avião"]),
        ("Airport", ["aeroporto"]),
        ("Station", ["estação"]),
        ("Bus Stop", ["parada de ônibus"]),
        ("Train", ["trem"]),
        ("Boat", ["barco", "navio"]),
        ("River", ["rio"]),
        ("Lake", ["lago"]),
        ("Sea", ["mar"]),
        ("Ocean", ["oceano"]),
        ("Forest", ["floresta"]),
        ("Mountain", ["montanha"]),
        ("Desert", ["deserto"]),
        ("Valley", ["vale"]),
        ("Island", ["ilha"]),
        ("City", ["cidade"]),
        ("Country", ["país"]),
        ("World", ["mundo"]),
        ("Family", ["família"]),
        ("Friend", ["amigo", "amiga"]),
        ("Brother", ["irmão"]),
        ("Sister", ["irmã"]),
        ("Father", ["pai"]),
        ("Mother", ["mãe"]),
        ("Son", ["filho"]),
        ("Daughter", ["filha"]),
        ("Uncle", ["tio"]),
        ("Aunt", ["tia"]),
        ("Cousin", ["primo", "prima"]),
        ("Grandfather", ["avô"]),
        ("Grandmother", ["avó"]),
        ("Husband", ["marido"]),
        ("Wife", ["esposa", "mulher"]),
        ("Food", ["comida"]),
        ("Drink", ["bebida"]),
        ("Water", ["água"]),
        ("Bread", ["pão"]),
        ("Milk", ["leite"]),
        ("Coffee", ["café"]),
        ("Tea", ["chá"]),
        ("Juice", ["suco"]),
        ("Beer", ["cerveja"]),
        ("Wine", ["vinho"]),
        ("Meat", ["carne"]),
        ("Chicken", ["frango"]),
        ("Fish", ["peixe"]),
        ("Egg", ["ovo"]),
        ("Vegetable", ["legume", "verdura"]),
        ("Fruit", ["fruta"]),
        ("Apple", ["maçã"]),
        ("Banana", ["banana"]),
        ("Orange", ["laranja"]),
        ("Lemon", ["limão"]),
        ("Rice", ["arroz"]),
        ("Pasta", ["macarrão"]),
        ("Salad", ["salada"]),
        ("Soup", ["sopa"])
    ]

    # Abre o arquivo para escrita
    with open('vocabulário_ingles.txt', 'w', encoding='utf-8') as file:
        for unidade in range(1, 101):  # Gera 100 unidades
            file.write(f"% Unidade {unidade}\n")
            
            # Seleciona um número aleatório de palavras por unidade (entre 5 e 10)
            num_palavras = random.randint(5, 10)
            palavras_selecionadas = random.sample(palavras_ingles, num_palavras)
            
            # Escreve cada palavra e suas traduções
            for palavra_ingles, traducoes_portugues in palavras_selecionadas:
                traducoes = ", ".join(traducoes_portugues)
                file.write(f"{palavra_ingles}: {traducoes};\n")
            
            file.write("\n")  # Linha em branco após cada unidade

# Executa a função para gerar o arquivo
gerar_vocabulário_ingles()
