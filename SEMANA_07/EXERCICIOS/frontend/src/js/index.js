
// Variavel que armazena todas as posições de possíveis vitórias
var possibleSolutions = [
    [1,2,3],
    [4,5,6],
    [7,8,9],
    [1,4,7],
    [2,5,8],
    [3,6,9],
    [1,5,9],
    [3,5,7]
]

// Classe que armazena todas as posições clicadas com o icone 'X'
// e também todas as posições clicadas com o icone 'Circle'
class Game {
    static qtdClicks = 0;
    static positionsX = [];
    static positionsCircle = [];
// Funcão da classe que checa qual jogador está jogando
    static check () {
        if (Game.qtdClicks%2) {
            return 1
        } else {
            return 0
        }
    }

// Função da classe que checa se o jogo já acabou
// se já acabou ele ve se deu velha ou se possui um vencedor
    static async gameOver (array, playerId) {
        if (compare(array) == 1) {
            await(fetch('http://localhost:3001/posta/resultado',{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                  },
                body: JSON.stringify(
                    {
                        playerWin: playerId == 1? "Jogador 1 venceu": "Jogador 2 venceu"
                    }
                )
            }))

            Game.qtdClicks = 0
            Game.positionsX = [];
            Game.positionsCircle = [];
            loopBox()
            return false
        }
        else if (Game.qtdClicks == 9) {
            await(fetch('http://localhost:3001/posta/resultado',{
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                  },
                body: JSON.stringify(
                    {
                        playerWin: "Deu velha"
                    }
                )
            }))
            Game.qtdClicks = 0
            Game.positionsX = [];
            Game.positionsCircle = [];
            loopBox()
            return false
        } 
        else {
            return true
        }
    }
}

// Função usada para setar as imagens de background das caixas após 
// a rodada do jogo acabar
function loopBox () {
    for (i of boxes) {
        i.setImage()
    }
}

// Função que compara as posições clicadas pelo usuário 
// com as posições de possíveis vitórias, se ocorrer uma possível vitória
// então irá haver um retorno de '1'
function compare (array) {
    for (var i = 0; i< possibleSolutions.length; i++) {
        var newArrayAnswer = array.sort().filter(
            (a) => {
                for (var j = 0; j < 3; j++) {
                    if (possibleSolutions[i][j] == a) {
                        return a
                    }
                }
            }
        )
        if (newArrayAnswer.length == 3) {
            return 1
            break
        } else {
            var newArrayAnswer;
    }
}
    return 0
}

// Classe responsável por atribuir métodos e atributos a cada caixa
class Box{
    constructor (boxId) {
        this.boxId = document.getElementById(boxId); // Atributo que pega o id da caixa

    }
// Função da classe que adiciona o icone na caixa e ainda acrescenta mais um na quantidade de cliques
    static addPoint(imageIcon, imageId) {
        document.getElementById(imageId).style.backgroundImage = `url('../../public/${imageIcon}')`
        Game.qtdClicks = Game.qtdClicks + 1
    }
// Método que adiciona um event handler na caixa
// que ao ser clicado acrescenta um ponto para o jogador, ou sendo "X" ou "Circle",
// E checar se houve "game over"


    player_mark () {
        this.boxId.addEventListener('click', function () {
            if (Game.check()) {
                Game.positionsCircle.push(parseInt(this.value))
                Box.addPoint('circulo.jpg', this.id)
                Game.gameOver(Game.positionsCircle, Game.check())
            } else {
                Game.positionsX.push(parseInt(this.value))
                Box.addPoint('x_preto.jpg', this.id)
                Game.gameOver(Game.positionsX, Game.check())
            }
        })
    }
// Método que seta as imagens para a próxima rodada
    setImage() {
        this.boxId.style.backgroundImage = `url('../../public/imagem_branco.jfif')`
    }
}
// Array que armazena a instância da classe para cada caixa
var boxes = [new Box('box-1'), new Box('box-2'), new Box('box-3'),
new Box('box-4'), new Box('box-5'), new Box('box-6'),
new Box('box-7'),new Box('box-8'),
new Box('box-9')]

// Loop que aciona o event handler de cada caixa
for (i of boxes) {
    i.player_mark()
}

