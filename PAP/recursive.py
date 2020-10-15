# Helpful functions:
def max(a, b):
    if( a > b ):
        return a
    else:
        return b

def min(a, b):
    if( a < b ):
        return a
    else:
        return b

# Exercicios:
def soma(n):
    if (n == 1):
        return 1
    else:
        return soma(n - 1) + n

def maior_da_lista(lista, tamanho):
    if(tamanho == 1):
        return lista[tamanho]
    return max(lista[tamanho-1], maior_da_lista(lista, tamanho-1))

def menor_da_lista(lista, tamanho):
    if(tamanho == 1):
        return lista[tamanho]
    return min(lista[tamanho-1], menor_da_lista(lista, tamanho-1))

def palindromo(palavra, tamanho):
    if(tamanho <= (len(palavra)/2) ):
        return True

    if(palavra[len(palavra) - tamanho - 1] == palavra[tamanho]):
        return palindromo(palavra, tamanho-1)
    else:
        return False

def is_palindrome(word):
    if(len(word) < 2): return True
    if(word[0] == word[-1]): return is_palindrome(word[1:-1])
    else: return False


def main():
    numeros = [-39, 17, 39, 44, -27, -37, 25, -31, 41, -44, 43, -15, -4, -10, 5, 29, -20, -31, 5, 12]
    palavra = "aibohphobia"
    print("\n\t### RECURSIVE ###\n")

    # ===== Exercício 1 =====
    print("Soma: " + str(soma(3)), end = "\n\n")

    # ===== Exercício 2 =====
    print("Maior: " + str(maior_da_lista(numeros, len(numeros))), end = "\n\n")

    # ===== Exercício 3 =====
    print("Menor: " + str(menor_da_lista(numeros, len(numeros))), end = "\n\n")

    # ===== Exercício 4 =====
    print("\"" + palavra, end="\" ")
    if(palindromo(palavra, len(palavra)-1)): print("is a palindrome")
    else: print("is not a palindrome")

    print("\"" + palavra, end="\" ")
    if (is_palindrome(palavra)): print("is a palindrome")
    else: print("is not a palindrome")


if __name__ == "__main__": main()
