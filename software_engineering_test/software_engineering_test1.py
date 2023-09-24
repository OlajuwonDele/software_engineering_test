def is_prime(n):
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0: #All primes greater than 3 are of the form 6k ± 1
        return False
    i = 5
    while i * i <= n: #Tesing only divisors up to the square root of the number n of interest. This loop is used to iterate through potential divisors.
        if n % i == 0 or n % (i + 2) == 0: #checks prime numbers of the form 6k ± 1, and it skips multiples of 2 and 3 as potential divisors by using this check.
            return False
        i += 6
    return True

def print_special_number(n):
    factors_dict = {
        3: "Ross ",
        5: "Robotics ",
        7: "Lucky ",
    }
    output = ""
    
    for factor, word in factors_dict.items(): #Makes use of dict type to determine if the given number is a factor of n
        if n % factor == 0:
            output += word
    
    if n % 3 == 0 and n % 5 == 0 and n % 7 == 0:
        output = "Jackpot!" #Replaces output if 3, 5, and 7 are factors of n

    if is_prime(n):
        output = "Prime "

    if output != "Jackpot!" or n == 0:
        if not output or n == 0:
            output = str(n) #Prints all other numbers 
        else:
            output = output[:-1] + "." #Replaces last element of output " " to "."
    
    return output

def main():
    start = int(input("Enter the starting range: "))
    end = int(input("Enter the ending range: "))
    
    for num in range(start, end + 1):
        result = print_special_number(num)
        print(result)

if __name__ == "__main__":
    main()