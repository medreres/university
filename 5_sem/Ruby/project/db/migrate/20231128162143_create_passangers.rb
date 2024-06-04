class CreatePassangers < ActiveRecord::Migration[7.0]
  def change
    create_table :passangers do |t|
      t.string :first_name
      t.string :last_name
      t.integer :items_count
      t.float :items_weight

      t.timestamps
    end
  end
end
