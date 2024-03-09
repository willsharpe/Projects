from cryptography.fernet import Fernet
import os
import sys

#checks if file is empty or not
def is_file_empty(file_path):
    return os.path.getsize(file_path)==0

#reads in the file and loops through to find the old password, then updates with the password with the new password
def update_password(old_pass, file_path, new_pass):
    modified_password = []
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            data=line.rstrip()
            user, passw=data.split("|")
            decrypted_pass=fer.decrypt(passw.encode()).decode()

            if decrypted_pass==old_pass:
                new_encrypted_pass=fer.encrypt(new_pass.encode()).decode()
                modified_password.append(f"{user}|{new_encrypted_pass}\n")

            else:
                modified_password.append(line)
        


    with open(file_path, 'w') as file:
            file.writelines(modified_password)

#generates the key to encrypt the password using Fernet
def gen_key():
    key = Fernet.generate_key()
    with open("key.key", "wb") as key_file:
        key_file.write(key)

#reads the key from they key.key file and returns the key
def load_key():
    file = open("key.key", "rb")
    key = file.read()
    file.close()
    return key

#adds an encrypted password to a text file 
def add_password(file_path):
    acct_name = input("Account Name: ")
    pwd = input("Password: ")
    with open(file_path, 'a') as file:
        file.write(acct_name + "|" + fer.encrypt(pwd.encode()).decode() + '\n')

#loops through the text file containing the account names and passwords and allows you to view all of them
def view_password(file_path):
    with open(file_path, 'r') as file:
        for line in file.readlines():
            data = line.rstrip()
            user, passw = data.split("|")
            print("User:", user, "| Password:", fer.decrypt(passw.encode()).decode())

key_file=sys.argv[1]
key = load_key()
fer = Fernet(key)


while True:
    response = input("Do you want to update a password, view a password, add a new password, or quit? ")

    if response == "update":
        retval=is_file_empty(key_file)
        if retval==1:
            print("There are no passwords to update")
        else:
            old_pass = input("Input your current password: ")
            new_password = input("Input updated password: ")
            update_password(old_pass, key_file, new_password)
            print("Your password has been updated ")

    if response == "view":
        view_password(key_file)
    if response == "add":
        add_password(key_file)
    if response == "quit":
        break
