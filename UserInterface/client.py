import requests
import time


api_base_url = "http://localhost:8080"


def redescribe_book():
    url_addition = "/redescribe/"
    id = input("Please enter a book ID: ")
    description = input("Enter the book description: ")

    description_json = {
        "DESCRIPTION": description
    }

    url = f"{api_base_url}{url_addition}{id}"
    response = requests.patch(url, json=description_json)

    if response.status_code != 200:
        print("Some error occurred when trying to redescribe book!")
    else:
        print("Book was added successfully")


def delete_book():
    url_addition = "/delete/"
    id = input("Please enter a book ID: ")
    url = f"{api_base_url}{url_addition}{id}"
    response = requests.delete(url)

    if response.status_code != 200:
        print("Some error occurred when trying to delete book!")
    else:
        print("Book was deleted successfully")


def update_book():
    url_addition = "/update/"
    id = input("Please enter a book ID: ")
    title = input("Enter the book title: ")
    author = input("Enter the book author: ")
    description = input("Enter the book description: ")

    book_json = {
        "TITLE": title,
        "AUTHOR": author,
        "DESCRIPTION": description
    }
    
    url = f"{api_base_url}{url_addition}{id}"
    response = requests.put(url, json=book_json)

    if response.status_code != 200:
        print("Some error occurred when trying to update book!")
    else:
        print("Book was added successfully")


def add_book():
    url_addition = "/add"
    title = input("Enter the book title: ")
    author = input("Enter the book author: ")
    description = input("Enter the book description: ")

    book_json = {
        "TITLE": title,
        "AUTHOR": author,
        "DESCRIPTION": description
    }
    
    url = f"{api_base_url}{url_addition}"
    response = requests.post(url, json=book_json)

    if response.status_code != 200:
        print("Some error occurred when trying to add book!")
    else:
        print("Book was added successfully")


def get_books():
    url_addition = "/?page="
    page_number = input("Please enter a page number: ")
    url = (f"{api_base_url}{url_addition}{page_number}") 
    response = requests.get(url)

    if (response.status_code != 200):
        print("Some error occured within the Library API!")
    elif (not response.content):
        if page_number == 1:
            print("No book records created!")
        else:
            print("No records for this page! Please try again!")
    else:
        print("\nBook List: ")
        for book in response.json():
            print(f"ID: {book['ID']}, Title: {book['TITLE']}, Author: {book['AUTHOR']}, Description: {book['DESCRIPTION']}")
        time.sleep(1)
       

def menu():
    exit = False

    while not exit:
        print("\nOptions Menu:")
        print("Type 'g' to get a list of the current books")
        print("Type 'a' to add a book")
        print("Type 'u' to update a book")
        print("Type 'd' to delete a book")
        print("Type 'r' to redescribe a book")
        print("Type 'q' to quit program")
        picked_option = input("Choice: ")
    
        match picked_option:
            case 'g':
                get_books()
            case 'a':
                add_book()
            case 'u':
                update_book()
            case 'd':
                delete_book()
            case 'r':
                redescribe_book()
            case 'q':
                exit = True
            case _:
                print("Invalid choice provided!! Please try again.")

if __name__ == "__main__":
    print("Welcome to the User Interface for the Library API")
    menu()
