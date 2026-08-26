import os
import torch
from transformers import GPT2LMHeadModel, GPT2Tokenizer
from transformers import TextDataset, DataCollatorForLanguageModeling
from transformers import Trainer, TrainingArguments, AutoTokenizer
from nltk.translate.bleu_score import sentence_bleu, SmoothingFunction

def calculate_bleu(generated_text, reference_text):
    # Simple whitespace tokenization
    ref_tokens = [reference_text.lower().split()]
    gen_tokens = generated_text.lower().split()
    
    # Use smoothing to avoid 0.0 scores when higher order n-grams are missing
    smoothie = SmoothingFunction().method1
    return sentence_bleu(ref_tokens, gen_tokens, smoothing_function=smoothie)

def generate_text(prompt, model, tokenizer, max_length=100, temperature=1.0, top_k=50, top_p=0.95):
    device = model.device
    inputs = tokenizer.encode(prompt, return_tensors="pt").to(device)
    
    attention_mask = torch.ones(inputs.shape, dtype=torch.long).to(device)
    #Top-k: Limit to the most probable k next-word.
    #Top-p: top next-word whose cumulative probability is p.
    outputs = model.generate(
        inputs,
        attention_mask=attention_mask,
        max_length=max_length,
        temperature=temperature,
        top_k=top_k,
        top_p=top_p,
        do_sample=True,
        pad_token_id=tokenizer.eos_token_id,
        num_return_sequences=1
    )
    
    return tokenizer.decode(outputs[0], skip_special_tokens=True)

def train_fine_tuned_model(train_file, output_dir="./poetry_model"):
    print(f"Fine-tune on file {train_file}...")
    model_name = "gpt2"
    tokenizer = GPT2Tokenizer.from_pretrained(model_name)
    model = GPT2LMHeadModel.from_pretrained(model_name)
    
    dataset = TextDataset(
        tokenizer=tokenizer,
        file_path=train_file,
        block_size=128
    )
    
    data_collator = DataCollatorForLanguageModeling(
        tokenizer=tokenizer, mlm=False
    )
    
    training_args = TrainingArguments(
        output_dir=output_dir,
        overwrite_output_dir=True,
        num_train_epochs=3,
        per_device_train_batch_size=4,
        save_steps=10_000,
        save_total_limit=2,
        logging_steps=500
    )
    
    trainer = Trainer(
        model=model,
        args=training_args,
        data_collator=data_collator,
        train_dataset=dataset,
    )
    
    trainer.train()
    
    trainer.save_model(output_dir)
    tokenizer.save_pretrained(output_dir)
    print(f"Model saved in {output_dir}")
    
    return tokenizer, model

def main():
    prompt = "In the forest Hoia-Baciu,"
    # Dummy reference text used to compute BLEU score for this prompt
    reference_text = (
        "In the forest Hoia-Baciu,\n"
        "Where the shadows intertwine,\n"
        "Spirits dance in silent circles,\n"
        "Underneath the ancient pine."
    )

    print("A: Pre-trained model generation")

    tokenizer_pre = GPT2Tokenizer.from_pretrained("gpt2")
    model_pre = GPT2LMHeadModel.from_pretrained("gpt2")
    
    print("\n--- (T=1.0, top_k=50, top_p=0.95) ---")
    gen_text_1 = generate_text(prompt, model_pre, tokenizer_pre, max_length=60)
    print(f"Generated:\n{gen_text_1}\n[BLEU Score: {calculate_bleu(gen_text_1, reference_text):.4f}]")
    
    print("\n--- (T=0.3) ---")
    gen_text_2 = generate_text(prompt, model_pre, tokenizer_pre, max_length=60, temperature=0.3)
    print(f"Generated:\n{gen_text_2}\n[BLEU Score: {calculate_bleu(gen_text_2, reference_text):.4f}]")
    
    print("\n--- (T=1.5) ---")
    gen_text_3 = generate_text(prompt, model_pre, tokenizer_pre, max_length=60, temperature=1.5)
    print(f"Generated:\n{gen_text_3}\n[BLEU Score: {calculate_bleu(gen_text_3, reference_text):.4f}]")

    t_bpe = AutoTokenizer.from_pretrained("gpt2")           # BPE
    t_wp = AutoTokenizer.from_pretrained("bert-base-uncased") # WordPiece
    t_sp = AutoTokenizer.from_pretrained("t5-small")        # SentencePiece / Unigram

    vers = "The floodwaters of the Danube reached Melk's library."

    print(f"\nGPT-2 (BPE): {t_bpe.tokenize(vers)}")
    print(f"BERT (WordPiece): {t_wp.tokenize(vers)}")
    print(f"T5 (SentencePiece): {t_sp.tokenize(vers)}\n")

    print("B: Fine-tuned model generation")
    
    train_file = "poetry_train.txt"
    model_dir = "./poetry_model"
    
    if os.path.exists(model_dir):
        print("Found fine-tuned model")
        tokenizer_ft = GPT2Tokenizer.from_pretrained(model_dir)
        model_ft = GPT2LMHeadModel.from_pretrained(model_dir)
    else:
        print("Start fine-tuning...")
        tokenizer_ft, model_ft = train_fine_tuned_model(train_file, model_dir)
        
    print("\n--- Default ---")
    gen_text_ft_1 = generate_text(prompt, model_ft, tokenizer_ft, max_length=60)
    print(f"Generated:\n{gen_text_ft_1}\n[BLEU Score: {calculate_bleu(gen_text_ft_1, reference_text):.4f}]")
    
    print("\n--- (top_k=10) ---")
    gen_text_ft_2 = generate_text(prompt, model_ft, tokenizer_ft, max_length=60, top_k=10)
    print(f"Generated:\n{gen_text_ft_2}\n[BLEU Score: {calculate_bleu(gen_text_ft_2, reference_text):.4f}]")

if __name__ == "__main__":
    main()