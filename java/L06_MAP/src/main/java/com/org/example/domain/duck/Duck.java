package com.org.example.domain.duck;

import com.org.example.domain.User;
import com.org.example.domain.card.Card;
import lombok.Getter;
import lombok.Setter;

import java.util.List;

@Getter
@Setter
public abstract class Duck extends User {
    private String type;
    private Double speed;
    private Double resistance;
    private Long cardId;

    public Duck(String username, String email, String password) {
        super(username, email, password);
    }

//    @Override
//    public String toString() {
//        return super.toString() + " | " + type + " | " + speed + " | " + resistance;
//    }

    @Override
    public String getUserType() {
        return "duck";
    }

    public abstract String getCardType();

    public abstract Card<? extends Duck> getCard(String name, List<Duck> members);

}
