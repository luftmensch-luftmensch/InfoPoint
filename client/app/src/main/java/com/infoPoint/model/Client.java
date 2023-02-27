/*
 * Scritto da Valentino Bocchetti il 25/2/2023 alle ore 14:42
 *
 * Copyright © 2023 InfoPoint
*/

package com.infoPoint.model;

public class Client {
    private String name;
    private String password;
    private ClientType type;

    // Constructors
    public Client() { }
    public Client(String name, String password, ClientType type) {
        this.name = name;
        this.password = password;
        this.type = type;
    }

    // GETTERS
    public String getName() { return name; }
    public String getPassword() { return password; }
    public ClientType getType() { return type; }

    // SETTERS
    public void setName(String name) { this.name = name; }
    public void setPassword(String password) { this.password = password; }
    public void setType(ClientType type) { this.type = type; }

    @Override
    public String toString() {
        return "Client{" +
                "name='" + name + '\'' +
                ", password='" + password + '\'' +
                ", type=" + type +
                '}';
    }
}