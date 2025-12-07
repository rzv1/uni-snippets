package com.org.example.domain.duck;

import com.org.example.domain.User;
import com.org.example.domain.card.Card;
import com.org.example.factory.DuckType;
import com.org.example.factory.UserType;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public abstract class Duck extends User {
    private DuckType type;
    private Double speed;
    private Double resistance;
    private Long cardId;

    public Duck(String username, String email, String password) {
        super(username, email, password);
    }

    @Override
    public String toString() {
        return getUserType() + " | " + speed + " | " + resistance;
    }

    @Override
    public UserType getUserType() {
        return UserType.DUCK;
    }

    public abstract Card<? extends Duck> getCard(String name, List<Duck> members);

}
